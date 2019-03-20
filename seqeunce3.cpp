#include <cstdlib>
#include <cassert>
#include "sequence3.h"
#include "node1.h"
/*
Invariant:
1. The items in the sequence are stored in the private member variable of 
   many_nodes.
2. The items are put into linked lists. The list head pointer is called head_ptr 
   and the list end pointer is tail_ptr. They both point to NULL when the 
   sequence is empty.
3. The current item is pointed towards the private member variable called cursor.
   There is also the precusor which points to the previous node from cursor. If 
   there is no current item then they are set to NULL.
*/
namespace main_savitch_5{
 
    sequence::sequence(){//Best Case: O(1) Worst Case: O(1) Average Case: O(1)
        cursor = NULL;   //As a Dynamic Array it's O(n) for all
        precursor = NULL;
        head_ptr = NULL;
        tail_ptr = NULL;
        many_nodes = 0;
    }
    sequence::sequence(const sequence& source){
    //Best Case: O(1) Worst Case: O(n) Average Case: O(n)
    //As a Dynamic Array: Best Case: O(1) Worst Case: O(n) Average Case: O(n)
        if(source.cursor == 0){                
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            cursor = NULL;
            precursor = NULL;
        }else if(source.cursor == source.head_ptr){
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            cursor = head_ptr;
            precursor = NULL;
        }else{
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            size_type position = 1;
            node *new_cursor = source.head_ptr;
            while(new_cursor != source.precursor){
                new_cursor = new_cursor->link();
                position++;
            }
            precursor = list_locate(head_ptr, position);
            cursor = precursor->link();
        }
        many_nodes = list_length(head_ptr);
        return;
    }
    sequence::~sequence(){
    //Best Case: O(1) Worst Case: O(n) Average Case: O(n) 
    //As a Dynamic Array: Best Case: O(1) Worst Case: O(n) Average Case: O(n)
        list_clear(head_ptr);
        many_nodes = 0;
    }
    void sequence::start(){
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //As a Dynamic Array: Best Case: O(n) Worst Case: O(n) Average Case: O(n)
        cursor = head_ptr;
        precursor = 0;
    }
    void sequence::advance(){
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //As a Dynamic Array: Best Case: O(n) Worst Case: O(n) Average Case: O(n)
        assert(is_item());
        precursor = cursor;
        cursor = cursor->link();
    }
    void sequence::insert(const value_type& entry){
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //Better Big-O function than Dynamic Array
        if(!is_item() || cursor == head_ptr){
            list_head_insert(head_ptr, entry);
            cursor = head_ptr;
            precursor = NULL;
            if(many_nodes == 0){
                tail_ptr = head_ptr;
            }
        }else{
            list_insert(precursor, entry);
            cursor = precursor->link();
        }
        ++many_nodes;
    }
    void sequence::attach(const value_type& entry){
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //Better Big-O function than Dynamic Array
        if(!is_item()){
            if(many_nodes == 0){
                list_head_insert(head_ptr, entry);
                tail_ptr = head_ptr;
                cursor = head_ptr;
            }else{
                precursor = tail_ptr;
                list_insert(precursor, entry);
                tail_ptr = tail_ptr->link();
                cursor = tail_ptr;
            }
        }else{
         precursor = cursor;
         list_insert(cursor, entry);
         cursor = cursor->link();
            if(precursor == tail_ptr){
                tail_ptr = tail_ptr->link();
            }
         }
     ++many_nodes;
    }
    void sequence::remove_current(){
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //Better Big-O function than Dynamic Array
        assert(is_item());
         if(cursor == head_ptr && cursor->link() != 0){
              list_head_remove(head_ptr);
              cursor = head_ptr;
              precursor = NULL;
           }else if(cursor == head_ptr && cursor->link() == 0){
                list_clear(head_ptr);
                cursor = NULL;
                precursor = NULL;     
           }else if(cursor->link() == 0){
               list_remove(precursor);
               cursor = NULL;
               precursor = NULL;
           }else{
               list_remove(precursor);
               cursor = precursor->link();
           }
           many_nodes = list_length(head_ptr);
           return;
    }
    void sequence::operator =(const sequence& source){
    //Best Case: O(1) Worst Case: O(n) Average Case: O(n)
    //Dynamic Array has a better Big-O function
        node *new_ptr;
        if(this == &source){
            return;
        }else{
            list_clear(head_ptr);
            list_copy(source.head_ptr, head_ptr, tail_ptr);
            many_nodes = source.many_nodes;
            if(source.cursor == NULL){
                cursor = NULL;
                precursor = NULL;
            }else if(source.cursor == source.head_ptr){
                cursor = head_ptr;
                precursor = NULL;
            }else{
                new_ptr = source.head_ptr;
                cursor = head_ptr;
                while(new_ptr != source.cursor){
                    new_ptr = new_ptr->link();
                    precursor = cursor;
                    cursor = cursor->link();
                }
            }
        }
    }
    sequence::size_type sequence::size() const{
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //As a Dynamic Array: Best Case: O(1) Worst Case: O(1) Average Case: O(1)
        return many_nodes;
    }
    bool sequence::is_item() const{
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //As a Dynamic Array: Best Case: O(1) Worst Case: O(1) Average Case: O(1)
        if(cursor == 0 || head_ptr == 0){
            return false;
        }else{
            return true;
        }
    }
    sequence::value_type sequence::current() const{
    //Best Case: O(1) Worst Case: O(1) Average Case: O(1)
    //As a Dynamic Array: Best Case: O(1) Worst Case: O(1) Average Case: O(1)
        return cursor->data();
    }
    
}