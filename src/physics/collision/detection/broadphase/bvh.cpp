#include "bvh.h"

AABBTree::AABBTree(float margin)
    : m_margin(margin)
{}

void AABBTree::update(std::size_t objects)
{
    if (m_root) {
        if ( m_root->is_leaf() ) {
            m_root->refit_AABB(m_margin);
        } else {
            m_invalid.clear();
            m_invalid.reserve(objects);
            populate_invalid_nodes(m_root);
            
            for (std::shared_ptr<Node>& node : m_invalid) {
                std::shared_ptr<Node> parent = node->parent;
                std::shared_ptr<Node> sibling = node->get_sibling();
                std::shared_ptr<Node> grandparent_parent_link = parent->parent ? (parent == parent->parent->left_child)
                    ? parent->parent->left_child : parent->parent->right_child
                : m_root;
                
                sibling->parent = parent->parent;
                grandparent_parent_link = sibling; // parent now deleted
                
                node->refit_AABB(m_margin);
                insert_node(node, m_root);
            }
            
            m_invalid.clear();
        }
    }
}

void AABBTree::populate_invalid_nodes(std::shared_ptr<Node>& root)
{
    if ( root->is_leaf() ) {
        Polygon& polygon = root->body->get_polygon();
        polygon.update_AABB();

        if ( !(root->enlarged.contains(polygon.m_box)) ) {
            m_invalid.push_back(root);
        }
    } else {
        populate_invalid_nodes(root->left_child);
        populate_invalid_nodes(root->right_child);
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