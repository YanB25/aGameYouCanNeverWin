//check: wait for more exactly check
//todo: unfinished coding
//temp: means you should delete this statement as soon as you start there
//maybe bug: check for parameter & of (shared_ptr<node>&) in functions
#include<iostream>
#include<vector>
#include<memory>
#include<algorithm>
#include<queue>
#include<assert.h>
using std::cin;
using std::cout;
using std::vector;
using std::shared_ptr;
using std::queue;
enum Initiative{Player,Computer};
const int FirstDeep = 3;
const int DeepLim = 10;
class node
{
public:
	enum { Lose = -1, Unknow, Win } ;
private:
	decltype(Lose) state;
	int deep;
	vector<int> computer;
	vector<int> player;
public:
	auto GetState() { return state; };
	auto GetDeep() { return deep; }
	decltype(Lose)& SetState() { return state; }
	vector<shared_ptr<node>> psons;
	node(shared_ptr<node>& pFather, int nth);
	node();
	node(const node&) = delete;
	node& operator =(const node&) = delete;
};
inline size_t ToLhs(int lhs) { return lhs / 2; }
inline size_t ToRhs(int rhs) { return rhs % 2; }
inline bool ComputerTurn(int deep) { return deep % 2 == 0; }
inline bool PlayerTurn(int deep) { return !ComputerTurn(deep); }
node::node():deep(0),state(Unknow)
{
	for (int i = 0; i < 2; ++i)
	{
		computer.push_back(1);
		player.push_back(1);
	}
	for (int i = 0; i < 4; ++i)
		psons.push_back(shared_ptr<node>());
}
node::node(shared_ptr<node>& pFather, int nth) : deep(pFather->deep + 1)
	, computer(pFather->computer), player(pFather->player)
{
	assert(nth >= 0 && nth < 4);
	assert(pFather->deep >= 0);
	assert(pFather->computer.size() == 2);
	assert(pFather->player.size() == 2);
	state = Unknow;

	//set ptr
	for (int i = 0; i < 4; ++i)
		psons.push_back(shared_ptr<node>());
	
	// set value and state
	if (PlayerTurn(deep))
	{
		player[ToLhs(nth)] += pFather->computer[ToRhs(nth)];
		player[ToLhs(nth)] %= 10;
		if (player[0] == 0 || player[1] == 0)
			state = Lose;
	}
	else
	{
		computer[ToLhs(nth)] = pFather->player[ToRhs(nth)];
		computer[ToLhs(nth)] %= 10;
		if (computer[0] == 0 || computer[1] == 0)
			state = Win;
	}

}
void factory(shared_ptr<node>& pFather)
{
	for (int i = 0; i < 4; ++i)
		pFather->psons[i] = std::make_shared<node>(pFather, i);
}
auto min(vector<shared_ptr<node>> psons)//todo
{
	return node::Lose;//temp
}
auto max(vector<shared_ptr<node>> psons)//todo
{
	return node::Lose;//temp
}
auto MaxMinAlg(shared_ptr<node>& pNode, int current_deep)//todo
{
	if (PlayerTurn(current_deep))
	{
		pNode->SetState() = min(pNode->psons);
	}
	else
	{
		pNode->SetState() = max(pNode->psons);
	}
}
auto SearchHelper(shared_ptr<node>& pNode, int deep_lim)
{
	if (pNode->GetState() == node::Win)
		return node::Win;
	else if (pNode->GetState() == node::Lose)
		return node::Lose;
	else return node::Unknow;
	if (pNode->GetDeep() > deep_lim)//check for >
		return node::Unknow;

	if (pNode->psons[0] == nullptr)
		factory(pNode);
	//todo
}
void InterativeSearch(shared_ptr<node>& p_root, int deep_lim = DeepLim)
{
	int first_deep = FirstDeep;
	for (int i = first_deep; i < deep_lim; ++i)
	{
		SearchHelper(p_root, i);
	}
}
int main()
{
	return 0;
}