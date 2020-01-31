#include "Search_tree.h"
#pragma once
template <class Record>
class AVL_tree: public Search_tree<Record> {
public:
   Error_code insert(const Record &new_data);
   Error_code remove(const Record &target);
protected:
   Error_code avl_insert(Binary_node<Record>* &sub_root, const Record &new_data, bool &taller);
   Error_code avl_delete(Binary_node<Record>* &sub_root, const Record &target, bool &shorter);
   //Error_code pre_delete(Binary_node<Record>* &sub_root, const Record &old_data, bool &shorter);
   //void avl_remove_root(Binary_node<Record>* &sub_root, bool &shorter, Record &predecessor, Binary_node<Record>* &to_delete);
   void left_balance(Binary_node<Record>* &sub_root);
   void right_balance(Binary_node<Record>* &sub_root);
   void rotate_left(Binary_node<Record>* &sub_root);
   void rotate_right(Binary_node<Record>* &sub_root);
   
};


template <class Record>
Error_code AVL_tree<Record>::insert(const Record &new_data)
/*
Post: If the key of new_data is already in the AVL_tree, a code
      of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the tree in such a way that the properties of
      an AVL tree are preserved.
Uses: avl_insert.
*/
{
   bool taller;
   return avl_insert(this->root, new_data, taller);
}


template <class Record>
Error_code AVL_tree<Record>::remove(const Record &target)
/*
Post: If a Record with a key matching that of target belongs to the
      AVL_tree, a code of success is returned, and the corresponding node
      is removed from the tree.  Otherwise, a code of not_present is returned.
Uses: Function search_and_destroy
*/

{
   bool shorter;
   return avl_delete(this->root, target, shorter);
 }


template <class Record>
Error_code AVL_tree<Record>::avl_insert(Binary_node<Record>* &sub_root,
           const Record &new_data, bool &taller)
/*
Pre:  sub_root is either NULL or points to a subtree of the AVL_tree
Post: If the key of new_data is already in the subtree, a
      code of duplicate_error is returned.
      Otherwise, a code of success is returned and the Record new_data
      is inserted into the subtree in such a way that the
      properties of an AVL tree have been preserved.
      If the subtree is increased in height, the parameter taller is set to
      true; otherwise it is set to false.
Uses: Methods of struct AVL_node; functions avl_insert
      recursively, left_balance, and right_balance.
*/
{
   Error_code result = success;
   if (sub_root == NULL) {
      sub_root = new AVL_node<Record>(new_data);
      taller = true;  //taller is true for every new node creation
   }
   else if (new_data == sub_root->data) {
      result = duplicate_error;
      taller = false;
   }
   //insert to LST
   else if (new_data < sub_root->data) {         
      result = avl_insert(sub_root->left, new_data, taller);

      if (taller == true)
		switch (sub_root->get_balance()) {
         case left_higher: //lh before insertion, now unbalanced, previous node says it was left_higher
            left_balance(sub_root);
            taller = false;       
            break;
		   case equal_height: 
            sub_root->set_balance(left_higher);
            break;  
         case right_higher:
            sub_root->set_balance(equal_height);
            taller = false;            
            break;
      }
   }
   //insert to RST
   else {                                     
      result = avl_insert(sub_root->right, new_data, taller);
      if (taller == true)
         switch (sub_root->get_balance()) {
         case left_higher:
            sub_root->set_balance(equal_height);
            taller = false;
            break;
         case equal_height:
            sub_root->set_balance(right_higher);
            break;
         case right_higher: 
            right_balance(sub_root);
            taller = false;        
            break;
         }
   }
   return result;
}


template <class Record>
Error_code AVL_tree<Record>::avl_delete(Binary_node<Record>* &sub_root, const Record &target, bool &shorter) {

   Error_code result = success;
   if (sub_root == nullptr){
      shorter = false;
      result = not_present;
   } else if (target == sub_root->data){
         if (sub_root->left != nullptr && sub_root->right != nullptr){
            Binary_node<Record> *to_delete = sub_root->left;
            shorter = true;
            while (to_delete->right != nullptr)
               to_delete = to_delete->right;
            sub_root->data = to_delete->data;
            avl_delete(sub_root->left, sub_root->data, shorter);

            if (shorter == true){
            switch (sub_root->get_balance()){
            case right_higher:
               //  test
               right_balance(sub_root);
               if (sub_root->get_balance() == equal_height) shorter = true;               
               break;
            case equal_height:
               sub_root->set_balance(right_higher);
               shorter = false;
              
               break;
            case left_higher:
               sub_root->set_balance(equal_height);
               shorter = true;
               
               break;
            }
         }

            
         } else if (sub_root->left == nullptr){
            shorter = true;
            Binary_node<Record> *to_delete = sub_root;
            sub_root = sub_root->right;
            delete to_delete;
            to_delete = nullptr;
         } else if (sub_root->right == nullptr) {
            shorter = true;
            Binary_node<Record> *to_delete = sub_root;
            sub_root = sub_root->left;
            delete to_delete;
            to_delete = nullptr;
         }
   
   } else if (target < sub_root->data){
      avl_delete(sub_root->left, target, shorter);

      std::cout << "recursion finished in left tree : balance checking here " << std::endl;

      if (shorter == true){
         switch (sub_root->get_balance()){
            case right_higher:
               //  test
               right_balance(sub_root);
               if (sub_root->get_balance() == equal_height) shorter = true;               
               break;
            case equal_height:
               sub_root->set_balance(right_higher);
               shorter = false;
               //shorter = true;
              
               break;
            case left_higher:
               sub_root->set_balance(equal_height);
               shorter = true;
               
               break;
         }
      }
   } else if (target  > sub_root->data) {
       avl_delete(sub_root->right, target, shorter);
      std::cout << "recursion finished in right tree : balance checking here " << std::endl;

       if (shorter == true){
         switch (sub_root->get_balance()){
            case left_higher:
               left_balance(sub_root);
               if (sub_root->get_balance() == equal_height) shorter = true;
               break;
            case right_higher:
               sub_root->set_balance(equal_height);
               shorter = true;
               break;
            case equal_height:
               // after deleting a node from RST, unbalanced now?
               sub_root->set_balance(left_higher);
               shorter = false;
               
               break;
         }

      }
   } 
   return success;
}




template <class Record>
void AVL_tree<Record>::left_balance(Binary_node<Record>* &sub_root)
/*
Pre:  sub_root points to a subtree of an AVL_tree that
      is doubly unbalanced on the .
Post: The AVL properties have been restored to the subtree.
Uses: rotate_left and rotate_right
      
*/
{
   Binary_node<Record>* &left_tree = sub_root->left;
   //single rotation 
   switch (left_tree->get_balance()){
      case equal_height:
         // node would have already been unbalanced
         std::cout << "WARNING: If you see this in an insertion, program error is detected in right_balance" << std::endl;
         // setting to the height, that it shold be and rotating to the left
         left_tree->set_balance(right_higher);
         rotate_right(sub_root);
         break;

      case left_higher: 
         sub_root->set_balance(equal_height); // review here, equal after the rotation 
         left_tree->set_balance(equal_height);
         rotate_right(sub_root);
         break;

      case right_higher: // double 
         Binary_node<Record> *sub_tree = left_tree->right;
         switch(sub_tree->get_balance()){ 
         case equal_height:
            sub_root->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            break;
         case left_higher:
            sub_root->set_balance(left_higher); 
            left_tree->set_balance(left_higher);
            break;
         case right_higher:
            sub_root->set_balance(equal_height); 
            left_tree->set_balance(left_higher);
            break;
      }
         sub_tree->set_balance(equal_height);
         rotate_left(left_tree);
         rotate_right(sub_root);  
         break; 
   }
      
      
}


template <class Record>
void AVL_tree<Record>::right_balance(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of an AVL_tree that
      is unbalanced on the right.
Post: The AVL properties have been restored to the subtree.
Uses: Methods of struct AVL_node;
      functions  rotate_right and rotate_left.
*/
{
   Binary_node<Record>* &right_tree = sub_root->right;
   // case right_higher: sigle left rotation
   // O  ub --> subroot
   //  \
   //   O  rh  --> right_tree
   //    \
   //     O
   switch (right_tree->get_balance()) {
   case right_higher:  //  single left rotation
      sub_root->set_balance(equal_height);
      right_tree->set_balance(equal_height);
      rotate_left(sub_root); //pointer adjustment
      break;


   case equal_height:  //  impossible case
      cout << "WARNING: If you see this in an insertion, program error is detected in right_balance" << endl;
      right_tree->set_balance(left_higher);
      rotate_left(sub_root);
      break;

   // case left_higher: double rotation left
   // O ub --> sub_root
   //  \
   //   O lh --> right_tree
   //  /
   // O three cases --> sub_tree
   case left_higher:                           
      Binary_node<Record> *sub_tree = right_tree->left;
	  //set balance of sub_root and right_tree assuming rotation is done
      switch (sub_tree->get_balance()) {
      case equal_height:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(equal_height);
         break;
      case left_higher:
         sub_root->set_balance(equal_height);
         right_tree->set_balance(right_higher);
         break;
      case right_higher:
         sub_root->set_balance(left_higher);
         right_tree->set_balance(equal_height);
         break;
      }
	  //set balance of sub_tree after rotation
      sub_tree->set_balance(equal_height);
	  //perform actual rotation
      rotate_right(right_tree);
      rotate_left(sub_root);
      break;
   }
}


//adjustment of pointers
template <class Record>
void AVL_tree<Record>::rotate_left(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of the AVL_tree.
      This subtree has a nonempty right subtree.
Post: sub_root is reset to point to its former right child, and the former
      sub_root node is the left child of the new sub_root node.
*/
{
   if (sub_root == NULL || sub_root->right == NULL)     //  impossible cases
      cout << "WARNING: program error detected in rotate_left" << endl;
   else {
      Binary_node<Record> *right_tree = sub_root->right;
      sub_root->right = right_tree->left; 
      right_tree->left = sub_root;
      sub_root = right_tree;
   }
}


template <class Record>
void AVL_tree<Record>::rotate_right(Binary_node<Record> *&sub_root)
/*
Pre:  sub_root points to a subtree of the AVL_tree.
      This subtree has a nonempty left subtree.
Post: 
*/
{
   Binary_node<Record>* left_tree = sub_root->left;
  
   if (sub_root == NULL || sub_root->left == NULL)
         cout << "WARNING: program error detected in rotate_left" << endl;
    else {
      sub_root->left = left_tree->right; // y-s right child  to be child of z's left 
      left_tree->right = sub_root;
      sub_root = left_tree;
   }
}






