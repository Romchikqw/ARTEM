#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

item *init(int key,char* info){
    item *root = calloc(1,sizeof(item));

    root->key = key;
    root->info = info;
    root-> parent = NULL;

    return root;
}

int get_thread(item *temp){
    item *ptr = temp->parent;
    if (temp->left) temp->threaded = temp->left;
    else if (temp->right) temp->threaded = temp->right;
    else if (!temp->left && !temp->right){
        if (ptr-> left == temp){
            while (!ptr -> right && ptr -> parent) ptr = ptr->parent;
            temp -> threaded = ptr -> right;
        }
        if (ptr->right == temp){
            item *temp1 = temp;
            while (ptr->right == temp1 && ptr->parent){
                temp1 = ptr;
                ptr = ptr->parent;
            }
            if (!ptr->parent && ptr->right == temp) return 1;
            temp ->threaded = ptr ->right;
        }
    }
    return 0;
}

int all_thread(item *root){
    item *ptr = root;
    get_thread(ptr);
    if (ptr->left) get_thread(ptr ->left);
    if (ptr->right) get_thread(ptr ->right);
    return 0;
}


int insert(item *root,int key,char *info){
    item *temp;
    item *ptr = root;

    item *newbranch = calloc(1,sizeof(item));
    newbranch->key = key;
    newbranch->info = info;

    if (ptr == NULL) return 1;

    while (ptr){
        temp = ptr;
        if ((newbranch->key)>=(ptr->key)) ptr = ptr->right;
        else ptr = ptr -> left;
    }

    if ( (newbranch->key) >= (temp->key) ){
        temp -> right = newbranch;
        newbranch->parent = temp;
        return 0;
    }
    else {
        temp -> left = newbranch;
        newbranch->parent = temp;
        return 0;
    }
}

item *search(item *root,int key){
    item *ptr = root;

    while (ptr){
        if (ptr->key == key) return ptr;
        if (ptr->key > key) ptr = ptr->left;
        else ptr = ptr->right;
    }

    return NULL;
}

item *search_max(item *root,int key){
    item *ptr = root;
    int max;

    while (ptr){
        if (ptr->key >= key){
            ptr = ptr->left;
        }
        else{
            max = ptr ->key;
            ptr = ptr->right;
        }
    }

    item *max1 = search(root,max);
    return max1;
}

item *min(item *root)
{
    item *l = root;
    while (l -> left != NULL)
        l = l -> left;
    return l;
}

item *getmin(item *root){
	item *p = root, *temp = NULL;
	if (p -> right != NULL)
        	return min(p -> right);
    	temp = p -> parent;
    	while ((temp != NULL) && (p == temp -> right))
    	{
        	p = temp;
    	        temp = temp -> parent;
    }
    return temp;
}


item *check_max(item *root){
    item *temp = root;
    while (temp->right ) temp = temp->right;
    return temp;
}


int delete(item *root,int key){
    item *temp = search(root,key);
    item *ptr = temp -> parent;

    if (!temp->left && !temp->right){
        if (ptr->left == temp) ptr->left = NULL;
        if (ptr->right == temp) ptr->right = NULL;
	free(temp->info);
        free(temp);
        return 0;
    }

    if ((temp->right && !temp->left) || (!temp->right && temp->left)){
        if (temp -> right) {
            item * pred = temp ->right;
            if (ptr->left == temp) {
                ptr->left = temp->right;
                pred -> parent = ptr ;
		free(temp->info);
                free(temp);
            }
            if (ptr->right == temp) {
                ptr->right = temp->right;
                pred -> parent = ptr ;
		free(temp->info);
                free(temp);
            }
        }
        if (temp -> left) {
            item * pred = temp ->left;
            if (ptr->left == temp) {
                ptr->left = temp->left;
                pred -> parent = ptr;
		free(temp->info);
                free(temp);
            }
            if (ptr->right == temp) {
                ptr->right = temp->left;
                pred -> parent = ptr ;
		free(temp->info);
                free(temp);
            }
        }
        return 0;
    }

    if (temp -> left && temp -> right){
        item *ptr = getmin(temp);
        temp->key = ptr->key;
        temp->info = ptr->info;
	if (ptr->parent->left == ptr){
		ptr -> parent -> left = NULL;
		printf("ASDAS\n");
	}
	if (ptr->parent->right == ptr){
		ptr -> parent -> right = NULL;
		printf("ASDAS\n");
	}
	free(ptr->info);
        free(ptr);
        }
        return 0;
}


void print(item *root) {
    item *ptr = root;

    if (!ptr) return;
    printf("\nKey:    %-3d\n",ptr->key);
    printf("Info:    %-3s\n",ptr->info);
    if (ptr->parent){
        item *temp = ptr->parent;
        printf("Parent:    %-3d\n", temp->key);
    }
    get_thread(ptr);
    if (ptr->threaded){
        printf("Thread:    %-3d\n\n",ptr->threaded->key);
   }
 //   if (ptr->key == max->key && !max->left) return;
//    printf("%d\n",max->key);
    print(ptr->left);
    print(ptr->right);

}

int clear(item *root){
    item *temp = root;
    if (temp->left){
        clear(temp->left);
    }
    if (temp->right){
        clear(temp->right);
    }
    free(temp->info);
    free(temp);
    return 0;
}
