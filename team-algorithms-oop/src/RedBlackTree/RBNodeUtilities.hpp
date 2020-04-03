#pragma once

namespace lab::forest::detail::rbutils {

    template <typename RBNode>
    bool hasRedChild(RBNode* node) {
        return (node->left != nullptr && node->left->color == RBNode::Color::Red) ||
               (node->right != nullptr && node->right->color == RBNode::Color::Red);
    }

    template <typename RBNode>
    void swapColors(RBNode* firstNode, RBNode* secondNode) {
        typename RBNode::Color temp = firstNode->color;
        firstNode->color = secondNode->color;
        secondNode->color = temp;
    }

    /**
     *
     * @brief Copy field of toCopy node to toPaste node, but without fields-pointers
     *
     */
    template <typename RBNode>
    void copyNodeData (RBNode* toCopy, RBNode* toPaste) {
        toPaste->data = toCopy->data;
        toPaste->color = toCopy->color;
    }

    /**
     * @param currNode parent node before rotation
     */
    template <typename RBNode>
    void rotateLeft(RBNode*& _root, RBNode*& currNode) {
        RBNode* currChildRight = currNode->right;
        currNode->right = currChildRight->left;

        if (currNode->right != nullptr) {
            currNode->right->parent = currNode;
        }

        currChildRight->parent = currNode->parent;

        if (currNode->parent == nullptr) {
            _root = currChildRight;
        } else if (currNode == currNode->parent->left) {
            currNode->parent->left = currChildRight;
        } else {
            currNode->parent->right = currChildRight;
        }

        currChildRight->left = currNode;
        currNode->parent = currChildRight;
    }

    /**
     * @param currNode parent node before rotation
     */
    template <typename RBNode>
    void rotateRight(RBNode*& _root, RBNode*& currNode) {
        RBNode* currChildLeft = currNode->left;
        currNode->left = currChildLeft->right;

        if (currNode->left != nullptr) {
            currNode->left->parent = currNode;
        }

        currChildLeft->parent = currNode->parent;

        if (currNode->parent == nullptr) {
            _root = currChildLeft;
        } else if (currNode == currNode->parent->left) {
            currNode->parent->left = currChildLeft;
        } else {
            currNode->parent->right = currChildLeft;
        }

        currChildLeft->right = currNode;
        currNode->parent = currChildLeft;
    }
}
