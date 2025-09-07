/*
ॐ				ॐ
  ओम नमः शिवाय
ॐ				ॐ
*/
#include<bits/stdc++.h>
using namespace std ;
typedef long long ll ;

struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) {
        data = val;
        left = right = NULL;
    }
};
void preOrder(Node* node){
  if(node==NULL)return ;

  cout << node->data << " " ;
  preOrder(node->left) ;
  preOrder(node->right) ;
}

void inOrder(Node* node){
  if(node==NULL) return ;

  inOrder(node->left);
  cout << node->data << " " ;
  inOrder(node->right) ;
}

void postOrder(Node* node){
  if(node==NULL) return ;
  
  postOrder(node->left) ;
  postOrder(node->right) ;
  cout << node->data << " " ;
}

vector<vector<int>> levelOrder(Node* node){
  vector<vector<int>> ans ;
  if(node==NULL) return ans ;
  queue<Node*> q ;
  q.push(node);

  while(!q.empty()){
    int size=q.size() ;

    vector<int> lvl ;

    for(int i=0 ;i<size ; i++){
      Node* it=q.front() ;
      q.pop() ;

      lvl.push_back(it->data) ;
      if(it->left!=NULL) 
      q.push(it->left) ;
      if(it->right!=NULL)
      q.push(it->right) ;

    }
    ans.push_back(lvl) ;
  }

  return ans ;

}

vector<int> preOrderTraversal(Node* node){
  vector<int> ans ;
  if(node==NULL) return ans ;

  stack<Node*> st ;
  st.push(node) ;

  while(!st.empty()){
    node=st.top() ;
    st.pop() ;
    ans.push_back(node->data) ;

    if(node->right!=NULL) st.push(node->right) ;
    if(node->left!=NULL) st.push(node->left) ;
  }
  return ans ;
}

vector<int> inOrderTraversal(Node* node){
  vector<int> ans ;

  stack<Node*> st ;
  

  while(true){
    if(node!=NULL){
      st.push(node) ;
      node=node->left;
    }
    else{
      if(st.empty()) break ;

      node=st.top() ;
      st.pop() ;
      ans.push_back(node->data) ;
      node=node->right ;
    }
  }
  return ans ;
}
vector<int> postOrderTraversalDoubleStack(Node* node){
  vector<int> ans ;
  if(node==NULL) return ans ;

  stack<Node*> st1,st2 ;

  st1.push(node) ;
  while(!st1.empty()){
    node=st1.top() ;
    st1.pop() ;
    st2.push(node) ;

    if(node->left!=NULL)st1.push(node->left) ;
    if(node->right!=NULL) st1.push(node->right) ;
  }

  while(!st2.empty()){
    ans.push_back(st2.top()->data) ;
    st2.pop() ;
  }
  return ans ;
}

vector<int> postOrderTraversalSingleStack(Node* root) {
    vector<int> ans;
    if (!root) return ans;

    stack<Node*> st;
    Node* curr = root;
    Node* lastVisited = NULL; // keep track of last visited node

    while (curr != NULL || !st.empty()) {
        if (curr != NULL) {
            st.push(curr);
            curr = curr->left;
        } else {
            Node* peekNode = st.top();
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                // if right child exists and not visited yet → go right
                curr = peekNode->right;
            } else {
                // visit node
                ans.push_back(peekNode->data);
                lastVisited = peekNode;
                st.pop();
            }
        }
    }
    return ans;
}

vector<int> preInPostTraversal(Node* node){
  stack<pair<Node*,int>> st ;
  st.push({node,1}) ;
  vector<int> pre,in,post ;

  if(node==NULL) return pre;

  while(!st.empty()){
    auto it=st.top() ;
    st.pop() ;
    if(it.second==1){
      pre.push_back(it.first->data) ;
      it.second++ ;
      st.push(it) ;
      if(it.first ->left!=NULL){
        st.push({it.first->left,1}) ;
      }
    }
    else if(it.second==2){
      in.push_back(it.first->data) ;
      it.second++ ;;
      if(it.first->right!=NULL) st.push({it.first->right,1});
    }
    else{
      post.push_back(it.first->data) ;
    }
  }
  // return pre;
  return in ;
  // return post ;
}
int main(){
    
    Node* root=new Node(1) ;
  // Level 1
    root->left = new Node(2);
    root->right = new Node(3);

    // Level 2
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    
    preOrder(root) ;
    cout << "\n" ;
    inOrder(root) ;
    cout << "\n" ;
    postOrder(root) ;
    cout << "\n" ;

    vector<vector<int>> bfs=levelOrder(root) ;

    int sz=bfs.size();
    for(int i=0 ;i<sz ;i++){
      cout << "LEVEL: " << i+1 << "\n" ;
      for(auto &val :bfs[i]){
        cout << val << " " ;
      }
      cout << "\n" ;
    }

    vector<int> check;
    check=preOrderTraversal(root) ;
    check=inOrderTraversal(root) ;
    check=postOrderTraversalDoubleStack(root) ;
    check=postOrderTraversalSingleStack(root) ;
    check=preInPostTraversal(root) ;


    for(auto &val :check)
      cout << val << " " ;
    cout << "\n" ;
    return 0 ;
}

