#include "bvh.h"
#include "gjk.h"
#include "epa.h"
#include <stack>

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
                std::vector<std::shared_ptr<Node>> invalids = get_invalid_nodes(m_root);
                
                for (std::shared_ptr<Node>& node : invalids) {
                    std::shared_ptr<Node>& parent = node->parent;
                    std::shared_ptr<Node>& sibling = node->get_sibling();
                    std::shared_ptr<Node>& grandparent_parent_link = parent->parent ? (parent == parent->parent->left_child)
                        ? parent->parent->left_child : parent->parent->right_child
                    : m_root;
                    
                    sibling->parent = parent->parent;
                    grandparent_parent_link = sibling; // parent now deleted
                    
                    node->refit_AABB(m_margin);
                    insert_node(node, m_root);
                }
            }
        }
    }

    std::vector<std::shared_ptr<Node>> AABBTree::get_invalid_nodes(std::shared_ptr<Node>& root)
    {
        std::vector<std::shared_ptr<Node>> invalids;
        invalids.reserve(m_objects->size());
        std::stack<std::shared_ptr<Node>> stack;

        stack.push(root);
        while (!stack.empty()) {
            std::shared_ptr<Node> node = stack.top();
            stack.pop();

            if ( node->is_leaf() ) {
                node->body->update_AABB();

                if ( !(node->enlarged.contains(node->body->get_AABB())) ) {
                    invalids.push_back(node);
                }
            } else {
                if (node->left_child) stack.push(node->left_child);
                if (node->right_child) stack.push(node->right_child);
            }
        }
        
        return invalids;
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
        std::shared_ptr<Node>& node = body->m_node;
        
        node->body = nullptr;
        body->m_node = nullptr;
        remove_node(node);
    }

    void AABBTree::remove_node(std::shared_ptr<Node>& node)
    {
        std::shared_ptr<Node>& parent = node->parent;
        
        if (parent) {
            std::shared_ptr<Node>& sibling = node->get_sibling();
            
            if (sibling) {
                sibling->parent = parent->parent;
                
                std::shared_ptr<Node>& grandparent_parent_link = parent == parent->parent->left_child ? parent->parent->left_child : parent->parent->right_child;
                grandparent_parent_link = sibling; // parent now deleted
            } else {
                m_root = sibling;
                sibling->parent = nullptr;
            }
        } else {
            m_root = nullptr; // node gets deleted
        }
    }

    std::vector<CollisionPair> AABBTree::query(CollisionBody* body) const
    {
        const AABB query = body->get_AABB();

        std::vector<CollisionPair> collisions;
        std::stack<std::shared_ptr<Node>> stack;
        
        stack.push(m_root);
        while (!stack.empty()) {
            std::shared_ptr<Node> node = stack.top();
            stack.pop();
            
            if (node->enlarged.collides(query)) {
                if (node->is_leaf() && node->body != body) {
                    Simplex2 simplex = GJK(body, node->body);
                    
                    if (simplex.contains_origin() ) {
                        Contact contact = EPA(simplex, body, node->body);
                        collisions.emplace_back(body, node->body, contact);
                    }
                } else {
                    if (node->left_child) stack.push(node->left_child);
                    if (node->right_child) stack.push(node->right_child);
                }
            }
        }
        
        return collisions;
    }

    std::vector<CollisionPair> AABBTree::get_collisions() const
    {
        std::vector<CollisionPair> collisions;
        
        for (CollisionBody* const body : *m_objects) {
            std::vector<CollisionPair> target_collisions = query(body);
            collisions.reserve(collisions.size() + target_collisions.size());
            collisions.insert(collisions.end(), target_collisions.begin(), target_collisions.end());
        }
        
        return collisions;
    }
}