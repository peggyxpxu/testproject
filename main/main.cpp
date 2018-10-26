#include<iostream>
#include<vector>
#include<stack>
#include<queue>
#include<string>
using namespace std;
struct TreeNode{
 int val;
 TreeNode *left;
 TreeNode *right;
 TreeNode(int x): val(x),left(NULL),right(NULL){}
};


//�ǵݹ���������
void PreOrder(TreeNode* T)
{
	stack<TreeNode*> s;
	TreeNode* p = T;
	while(p||!s.empty())
	{
		while(p!=NULL)
		{
			cout<<p->val<<" ";
			s.push(p);
			p = p->left;
		}
		if(!s.empty())
		{
			p = s.top();
			s.pop();
			p = p->right;
		}
	
	}
}
//�ǵݹ��������
void MidOrder(TreeNode* T)
{
   stack<TreeNode*> s;
   TreeNode *p = T;
   while(p||!s.empty())
   {
	 while(p)
	 {
		 s.push(p);
		 p = p->left;
	 }
	 if(!s.empty())
	 {
		 p = s.top();
		 cout<<p->val<<" ";
		 s.pop();
		 p = p->right;
	 } 
   }
}
//! �ǵݹ�������
void PostOrder(TreeNode* T)
{
	stack<TreeNode*> s;
	TreeNode *cur;//��ǰ�ڵ�
	TreeNode *pre = NULL;//ǰһ�α����ʵĽڵ�
	s.push(T);
	while(!s.empty())
	{
		cur = s.top();
		if((!cur->left&&!cur->right)||//û�����Һ���
			(pre!=NULL&&(pre==cur->left||pre==cur->right)))//���Һ����Ѿ������ʹ���
		{
			cout<<cur->val<<" ";
			s.pop();
			pre = cur;
		}
		else//���ν���������ջ
		{
			if(cur->right)
				s.push(cur->right);
			if(cur->left)
				s.push(cur->left);
		}
	}
} 
//��֪�����������������
TreeNode* reConstructTree(vector<int> pre,vector<int> vin)
{
	if(vin.size()==0)
	{
		return NULL;
	}
	//ǰ��ĵ�һ�����Ǹ��ڵ�
	int val = pre[0];
	if(vin.size()==1)
	{
		return new TreeNode(val);
	}
	TreeNode* root = new TreeNode(val);
	int i = 0;
	int index = 0;
	//�ҵ����ڵ���������ĸ�λ��
	for(i=0;i<vin.size();i++)
	{
		if(vin[i]==root->val)
		{
		    index  = i;
			break;
		}
			
	}
	vector<int> frontleft(pre.begin()+1,pre.begin()+index+1),
		frontright(pre.begin()+index+1,pre.end()),
		midleft(vin.begin(),vin.begin()+index),
		midright(vin.begin()+index+1,vin.end());
	int len1=0,len2=0;
	////������
	//for(int i=0;i<index;i++)
	//{
	//	len1++;
	//	midleft.push_back(vin[i]);
	//}
	//for(int i=index+1;i<vin.size();i++)
	//{
	//	len2++;
	//	midright.push_back(vin[i]);
	//}
	////������
	//for(int i=1;i<=len1;i++)
	//{
	//	frontleft.push_back(pre[i]);
	//}
	//for(int i=len1+1;i<pre.size();i++)
	//{
	//	frontright.push_back(pre[i]);
	//}
	root->left = reConstructTree(frontleft,midleft);
	root->right = reConstructTree(frontright,midright);
}
/**********�������Ŷ�����*************/
TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2)
{
	if (!t1&&!t2)
	{
		return NULL;
	}
	if (t1!=NULL&&t2==NULL)
	{
		return t1;
	}
	else if (t1==NULL&&t2!=NULL)
	{
		return t2;
	}
	else if(t1!=NULL&&t2!=NULL)
	{
		t1->val=t1->val+t2->val;
		t1->left=mergeTrees(t1->left,t2->left);
		t1->right=mergeTrees(t1->right,t2->right);
		return t1;
	}
}
//������������
int getDepth(TreeNode* root,int n)
{
	if(!root)
		return n;
	else
		return max(getDepth(root->left,n+1),getDepth(root->right,n+1));
}
/**********�ж�ƽ�������**************/
bool isBalanced(TreeNode* root) {
	if (root==NULL)
	{
		return true;
	}
	int leftDepth=getDepth(root->left,1);
	int rightDepth=getDepth(root->right,1);
	if (abs(leftDepth-rightDepth)>1)
	{
		return false;
	}
	else 
		return isBalanced(root->left)&&isBalanced(root->right);
}

//��ת������
TreeNode* reverseTree(TreeNode* t1)
{
	if(t1==NULL)
		return NULL;
	else
	{
		TreeNode *left = t1->left,*right = t1->right;
		t1->left = reverseTree(right);
		t1->right = reverseTree(left);
		return t1;
	}
}
bool isSameTree(TreeNode* t1,TreeNode* t2)
{
	if(!t1&&!t2)
		return true;
	if(!t1&&t2)
		return false;
	if(t1&&!t2)
		return false;
	if(t1->val!=t2->val)
		return false;
	else
		return isSameTree(t1->left,t2->left)&&isSameTree(t1->right,t2->right);
}
bool isSymmetrical(TreeNode* pRoot)
{
	if(pRoot==NULL)
		return true;
	pRoot->right = reverseTree(pRoot->right);
	bool ans = isSameTree(pRoot->left,pRoot->right);
	return ans;
}
//�ж�����
bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2)
{
	if(!pRoot2&&!pRoot1)
        return false;
    if(!pRoot2||!pRoot1)
        return false;
    if(isSameTree(pRoot1,pRoot2))
        return true;
    else
    return HasSubtree(pRoot1->left,pRoot2)||HasSubtree(pRoot1->right,pRoot2);
            
}
/***********�ҵ�����������͹�ͬ����**************/
/*���� ��������Ҫ�ص㣺���ӱȸ��ڵ�С���Һ��ӱȸ��ڵ��*/ 

TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {

	if (p->val<root->val&&q->val<root->val)
	{
			return  lowestCommonAncestor(root->left,p,q);
	}
	if (p->val>root->val&&q->val>root->val)
	{
			return lowestCommonAncestor(root->right,p,q);
	}
	else 
		return root; 
}
//��һ�������ǲ��Ƕ����������ĺ����������
//BST�ĺ������еĺϷ������ǣ�����һ������S�����һ��Ԫ����x ��Ҳ���Ǹ�����
//���ȥ�����һ��Ԫ�ص�����ΪT��
//��ôT���㣺T���Էֳ����Σ�ǰһ�Σ���������С��x����һ�Σ�������������x���������Σ����������ǺϷ��ĺ������С�
bool VerifySquenceOfBST(vector<int> sequence) {
	int lenth = sequence.size();
	int i = 0;
	while(--lenth)
	{
		while(sequence[i++]<sequence[lenth]);
		while(sequence[i++]>sequence[lenth]);
		if(i<lenth)
			return false;
		i = 0;
	}
	return true;
}
//�������������к�Ϊĳһ��ֵ��·��
void helpFind(TreeNode* root,int expectNumber,vector<vector<int>> &ans,vector<int> &nums)
{
	if(!root->left&&!root->right)
	{
		int sum = 0;
		for(int i=0;i<nums.size();i++)
		{
			sum+=nums[i];
		}
		if(sum == expectNumber)
			ans.push_back(nums);
	}
	if(root->left)
	{
		nums.push_back(root->left->val);
		helpFind(root->left,expectNumber,ans,nums);
		nums.pop_back();
	}
	if(root->right)
	{
		nums.push_back(root->right->val);
		helpFind(root->right,expectNumber,ans,nums);
		nums.pop_back();
	}
}
vector<vector<int>> FindPath(TreeNode* root,int expectNumber)
{
	vector<vector<int>> ans;
	vector<int> nums;
	if(!root)
        return ans;
	nums.push_back(root->val);
	helpFind(root,expectNumber,ans,nums);
	return ans;
}
//����������������  

char* Serialize(TreeNode *root) 
{    
	if(!root) return "#";
	string r = to_string(long double(root->val));
	r.push_back(',');
	char *left = Serialize(root->left);
	char *right = Serialize(root->right);
	char *ret = new char[strlen(left)+strlen(right)+r.size()];
	strcpy(ret,r.c_str());
	strcat(ret,left);
	strcat(ret,right);
	return ret;
}
//�����ַ�����ȡ������
TreeNode* decode(char *&str)
{
	if(*str=='#')
	{	
		str++;
		return NULL;
	}
	int num=0;
	while(*str != ',')
		num =num*10+(*(str++)-'0');
	str++;
	TreeNode *root = new TreeNode(num);
	root->left = decode(str);
	root->right = decode(str);
	return root;
}
TreeNode* Deserialize(char *str) 
{
	return decode(str); 
}
int FindComma(char s[], int len)
{
    int match = 0;
    int i;
    for(i = 0; i < len; i++)
    {
        if(s[i] == '(')
            ++match;
        else if(s[i] == ')')
            --match;
        if(match==0 && s[i]==',')
            break;
    }
    return i;
}


TreeNode * CreateBiTree(char s[], int len)
{
    if(len <= 0)
        return NULL;
    //if(s[0] == '#')
    //    return NULL;
	int num = 0;
	while(*s>='0'&&*s<='9')
	{
		num = num*10 + *(s++)-'0';
		len--;
	}
	TreeNode *root = new TreeNode(num);
    if(len == 1)
    {
        root->left = NULL;
        root->right = NULL;
    }
    else
    {
        int commaPos = FindComma(s+1, len-1);
        root->left = CreateBiTree(s+1, commaPos);
        root->right = CreateBiTree(s+1+commaPos+1,len-2-commaPos-1);
    }
    return root;
}
string ss = "1(2(4,5(7,8)),3(6))";
void parseTree(TreeNode* Tree,string &str){
    if(Tree!=NULL){
		str += to_string(long double(Tree->val));
		if(Tree->left||Tree->right){
			str.push_back('(');
			parseTree(Tree->left,str);
            if(Tree->right){
				str.push_back(',');
                parseTree(Tree->right,str);
            }
           str.push_back(')');
        }
    }
}

 /******������ȱ���********/
void breadthFirstSearch(TreeNode* root)
{
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		TreeNode *node = q.front();
		cout<<node->val<<endl;
		q.pop();
		if(node->left)
			q.push(node->left);
		if(node->right)
			q.push(node->right);
	}
}
/******������ȱ���********/
void depthFirstSearch(TreeNode* root)
{
	stack<TreeNode*> s;
	s.push(root);
	while(!s.empty())
	{
		TreeNode* node = s.top();
		cout<<node->val<<endl;
		s.pop();
		if(node->left)
			s.push(node->left);
		if(node->right)
			s.push(node->right);
	}
}
/***********�ж϶��������¶�***************/
int posterOrder(TreeNode *root,int &Tilt)
{
	if(!root) return 0;
	int leftsum = posterOrder(root->left,Tilt);
	int rightsum = posterOrder(root->right,Tilt);
	Tilt += abs(leftsum-rightsum);
	return rightsum+leftsum+root->val;
}
int findTilt(TreeNode *root)
{
	int Tilt = 0;
	posterOrder(root,Tilt);
	return Tilt;
}

//������************�ж϶�������ֱ��**************/
int helpDiameter(TreeNode* root,int &diameter)
{
	if(!root) return 0;
	int left = helpDiameter(root->left,diameter);
	int right = helpDiameter(root->right,diameter);
	if(left+right>diameter)
		diameter = left+right;
	return max(left,right)+1;
}
int diameterOfBinaryTree(TreeNode* root)
{
	int diameter = 0;
	helpDiameter(root,diameter);
	return diameter;
}

//������*******�жϸ��ڵ㵽Ҷ�ӽڵ�����ľ���*********
int minDepth(TreeNode* root)
{
	if(!root) return 0;
	int left  = minDepth(root->left);
	int right = minDepth(root->right);
	if(left==0)
		return right+1;
	if(right==0)
		return left+1;
	else
		return min(left,right)+1;
}
//ÿһ���ƽ��ֵ
vector<double> averageOfLevels2(TreeNode* root)
{
	vector<double> ans;
	queue<TreeNode*> q;
	q.push(root);
	while(!q.empty())
	{
		int lenth = q.size();
		double sum = 0;
		for(int i=0;i<lenth;i++)
		{
			TreeNode* node = q.front();
			sum += node->val;
			q.pop();
			if(node->left) q.push(node->left);
			if(node->right) q.push(node->right);

		}
		ans.push_back(sum/double(lenth));
	}
	return ans;
}
//����Ҷ�ӽ��ĺ�
int sumAll = 0;
int sumOfLeaves(TreeNode* root)
{
	if(!root) return sumAll;
	else
	{
		if(!root->left && !root->right)
		{
			sumAll+=root->val;
		}
		sumOfLeaves(root->left);
		sumOfLeaves(root->right);
		return sumAll;
	}
}
///******�����������Ҷ�ӽڵ�ĺ�*********/
int sumL;
int sumOfLeftLeaves(TreeNode* root)
{
	if(!root) return sumL;
	else
	{
		if(root->left)
		{
			if(!root->left->left&&!root->right->right)
				sumL += root->val;
		}
		sumOfLeftLeaves(root->left);
		sumOfLeftLeaves(root->right);
		return sumL;
	}
}
/******�����������Ҷ�ӽڵ�ĺ�*********/
 int sumR = 0;
 int sumOfRightLeaves(TreeNode* root)
 {
	 if(!root) return sumR;
	 else
	 {
		 if(root->right)
		 {
			 if(!root->right->right&&!root->left->left)
				 sumR+=root->val;
		 }
	 }
	 sumOfRightLeaves(root->left);
	 sumOfRightLeaves(root->right);
	 return sumR;
 }
 /**********��������Ѱ�Ҷ������к�������*******/
int maxTreelink(TreeNode* root)
{
	if(!root->left&&!root->right)
		return root->val;
	else
	{
		int lsum = 0,rsum = 0;
		if(root->left)
			lsum = maxTreelink(root->left);
		if(root->right)
			rsum = maxTreelink(root->right);
		return max(lsum,rsum)+root->val;
	}
		

}
//����������
//����
bool insertBST(TreeNode* &t,int val)
{
	TreeNode *node = new TreeNode(val);
	if(!t)
	{
		t = node;
		return true;
	}
	else
	{
		if(val==t->val)
		{
			return false;
		}
		else if(val<t->val)
		{
			insertBST(t->left,val);
		}
		else
		{
			insertBST(t->right,val);
		}
	}
}
//����
TreeNode* createBST(vector<int> nums)
{
	TreeNode* t;
	for(int i=0;i<nums.size();i++)
	{
		insertBST(t,nums[i]);
	}
	return t;
}

//����
bool findBST(TreeNode* t,int val)
{
	if(!t)
		return false;
	if(val==t->val)
		return true;
	if(val<t->val)
		return findBST(t->left,val);
	else
		return findBST(t->right,val);
}
//ɾ��
bool deleteBST(TreeNode* t,int val)
{
	if(!t)
		return false;
	if(val==t->val)
	{
		if(!t->left)
			t = t->right;
		if(!t->right)
			t = t->left;
		else
		{
			TreeNode *p = t,*l = t->left;
			while(l->right)
			{
				p = l;
				l = l->right;
			}
			t->val = l->val;
			if(p==t)
				p->left = l->left;
			else
				p->right = l->left;
		}
		return true;
	}
	if(val<t->val)
		return deleteBST(t->left,val);
	else
		return deleteBST(t->right,val);
}
int main()
{
	char str[] = "11(22(444,5(7,8)),3(6))";
	TreeNode *root = CreateBiTree(str,strlen(str));
	//string ans;
	//parseTree(root,ans);
	//cout<<ans<<endl;
	int n;
	cin>>n;
	vector<int> pre(n,0),vin(n,0);
	for (int i=0;i<n;i++)
	{
		cin>>pre[i];
	}
	for (int i=0;i<n;i++)
	{
		cin>>vin[i];
	}
//	TreeNode* root = reConstructTree(pre,vin);
	//1248##9##5##36##7##
	//TreeNode *head1 = new TreeNode(0);
	//TreeNode *head2 = new TreeNode(2);
	//createTree(head1);
	//int a = maxTreelink(head1);
	//char * ans = Serialize(head1);
	//cout<<ans<<endl;
	////createTree(head2);
	//FindPath(head1,22);
	//HasSubtree(head1,head2);
	////isSymmetrical(head1);
	///*PreOrder(head1);*/
	////MidOrder(head1);
	////PostOrder(head1);
	while(1);
}