#include "bvh.h"
#include "epa.h"
#include "gjk.h"

namespace Physics
{
    AABBTree::AABBTree(float margin)
        : m_margin(margin)
    {}

    void AABBTree::update()
    {
        if (m_root) {
            if ( m_root->is_leaf() ) {
                m_root->refit_AABB(m_margin);
            } else {
                m_invalids.clear();
                m_invalids.reserve(m_objects->size());
                update_invalid_nodes(m_root);
                
                for (std::shared_ptr<Node>& node : m_invalids) {
                    std::shared_ptr<Node>& parent = node->parent;
                    std::shared_ptr<Node>& sibling = node->get_sibling();
                    std::shared_ptr<Node>& grandparent = parent->parent;
                    // Get grandparents pointer to parent
                    std::shared_ptr<Node>& grandparent_parent_link =
                        grandparent ?
                            parent == grandparent->left_child ?
                                grandparent->left_child
                            : grandparent->right_child
                        : m_root;

                    sibling->parent = grandparent;
                    grandparent_parent_link = sibling; // parent now deleted
                    
                    node->refit_AABB(m_margin);
                    insert_node(node, m_root);
                }
                
                m_invalids.shrink_to_fit();
            }
        }
    }

    void AABBTree::update_invalid_nodes(std::shared_ptr<Node>& node)
    {
        if ( node->is_leaf() ) {
            node->body->update_AABB();

            if ( !(node->enlarged.contains(node->body->get_AABB())) ) {
                m_invalids.push_back(node);
            }
        } else {
            update_invalid_nodes(node->left_child);
            update_invalid_nodes(node->right_child);
        }
    }

    void AABBTree::insert(CollisionBody* body)
    {
        if (m_root) {
            std::shared_ptr<Node> node = std::make_shared<Node>();
            node->make_leaf(body);
            node->refit_AABB(m_margin);
            insert_node(node, m_root);
        } else {
            m_root = std::make_shared<Node>();
            m_root->make_leaf(body);
            m_root->refit_AABB(m_margin);
        }
    }

    void AABBTree::insert_node(std::shared_ptr<Node>& node, std::shared_ptr<Node>& parent)
    {
        if ( parent->is_leaf() ) {
            std::shared_ptr<Node> branch = std::make_shared<Node>();
            branch->parent = parent->parent;
            branch->make_branch(node, parent);
            parent = branch;
        } else {
            const AABB& left = parent->left_child->enlarged;
            const AABB& right = parent->right_child->enlarged;
            
            const float delta_left = left.Union(&(node->enlarged)).area() - left.area();
            const float delta_right = right.Union(&(node->enlarged)).area() - right.area();
            
            if (delta_left < delta_right) {
                insert_node(node, parent->left_child);
            } else {
                insert_node(node, parent->right_child);
            }
        }
        
        parent->refit_AABB(m_margin);
    }

    void AABBTree::remove(CollisionBody* body)
    {
        std::shared_ptr<Node>& node = body->get_node();
        
        node->body = nullptr;
        body->set_node(nullptr);
        remove_node(node);
    }

    void AABBTree::remove_node(std::shared_ptr<Node>& node)
    {
        std::shared_ptr<Node>& parent = node->parent;
        
        if (parent) {
            std::shared_ptr<Node>& sibling = node->get_sibling();
            
            if (sibling) {
                sibling->parent = parent->parent;
                
                std::shared_ptr<Node>& grandparent = parent->parent;
                std::shared_ptr<Node>& grandparent_parent_link =
                    parent == grandparent->left_child ?
                        grandparent->left_child
                    : grandparent->right_child;

                grandparent_parent_link = sibling; // parent now deleted
            } else {
                m_root = sibling;
                sibling->parent = nullptr;
            }
        } else {
            m_root = nullptr;
        }
    }

    std::vector<CollisionPair>& AABBTree::get_collisions()
    {
        m_collisions.clear();

        if (!m_root || m_root->is_leaf()) {
            return m_collisions;
        } else {
            clear_crossed_flags(m_root);
            compute_collisions(m_root->left_child, m_root->right_child);
        }

        clear_crossed_flags(m_root);

        m_collisions.shrink_to_fit();
        return m_collisions;
    }

    void AABBTree::cross_children(std::shared_ptr<Node>& node)
    {
        if (!node->children_crossed) {
            compute_collisions(node->left_child, node->right_child);
            node->children_crossed = true;
        }
    }

    void AABBTree::clear_crossed_flags(std::shared_ptr<Node>& node)
    {
        node->children_crossed = false;

        if (!node->is_leaf()) {
            clear_crossed_flags(node->left_child);
            clear_crossed_flags(node->right_child);
        }
    }

    void AABBTree::compute_collisions(std::shared_ptr<Node>& a, std::shared_ptr<Node>& b)
    {
        if (a->is_leaf()) {
            if (b->is_leaf()) {
                const AABB& aabb_a = a->body->get_AABB();
                const AABB& aabb_b = b->body->get_AABB();

                if (aabb_a.collides(aabb_b)) {
                    Simplex2 simplex = GJK(a->body, b->body);
                    
                    if (simplex.contains_origin() ) {
                        Contact contact = EPA(simplex, a->body, b->body);
                        m_collisions.emplace_back(a->body, b->body, contact);
                    }
                }
            } else {
                cross_children(b);

                compute_collisions(a, b->left_child);
                compute_collisions(a, b->right_child);
            }
        } else {
            if (b->is_leaf()) {
                cross_children(a);

                compute_collisions(a->left_child, b);
                compute_collisions(a->right_child, b);
            } else {
                cross_children(a);
                cross_children(b);

                compute_collisions(a->left_child, b->left_child);
                compute_collisions(a->left_child, b->right_child);
                compute_collisions(a->right_child, b->left_child);
                compute_collisions(a->right_child, b->right_child);
            }
        }
    }
}
