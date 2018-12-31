/*
	Lesson learned:
	Plan stuff out. Visualize data relationships, track all that needs to be set after an operation. Invariants.
	Psuedocode, inspect it makes all needed changes.

	Need unit test after coding a small bit at a time. List push front pointer assigns out of order and not used temps...

	Also: look at other peoples impl's if can.
	Dont think something is super trivial and blind code a lot without verifying.

	hmap insert, wrap around, no keys marked avail, all deleted or occupied.
*/

#if 0
Design and implement a data structure for Least Recently Used(LRU) cache.It should support the following operations : get and put.

get(key) - Get the value(will always be positive) of the key if the key exists in the cache, otherwise return -1.
put(key, value) - Set or insert the value if the key is not already present.When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.

Follow up :
Could you do both operations in O(1) time complexity ?

Example :

	LRUCache cache = new LRUCache(2 /* capacity */);

cache.put(1, 1);
cache.put(2, 2);
cache.get(1);       // returns 1
cache.put(3, 3);    // evicts key 2
cache.get(2);       // returns -1 (not found)
cache.put(4, 4);    // evicts key 1
cache.get(1);       // returns -1 (not found)
cache.get(3);       // returns 3
cache.get(4);       // returns 4
#endif

//is any constraint on key range, besides [0, INT_MAX] ? does not appear so.

#ifdef _MSC_VER
inline unsigned bsr(unsigned a)
{
	unsigned long i;
	_BitScanReverse(&i, a);
	return i;
}
#else
#define bsr(a) (__builtin_clz(a)^31u)
#endif

//n: 0 -> undefined
//n: 1 -> 0
//n: 2 -> 1
//n: 3 -> 2
//n: 4 -> 2
//n: 5 -> 3
//undefined if the true result would be >= 32
inline unsigned ceil_ilog2(unsigned n)
{
	return bsr(n*2 - 1);
}

struct Node;

struct Bucket
{
	int k;
	Node *pNode;
};

struct Node
{
	Bucket *pBucket;
	int val;
private:
	int iprev;
	int inext;

	friend class DList;
};

//note this doesnt store the value associated to the LRU cache, but nodeIndexes. nodes have those.
struct HashMap
{
	struct InsertResult
	{
		Bucket *pBucket;
		bool inserted;
	};
private:
	enum : int {
		Avail = -1,
		Tombstone = -2
	};

	Bucket *buckets;
	unsigned mask;//==nBuckets-1

	void print() { for (unsigned i = 0; i <= mask; ++i) printf("% 2d", buckets[i].k); putchar('\n'); }
public:
	~HashMap()
	{
		free(buckets);
	}

	HashMap(unsigned cap)
	{
		unsigned nbuckets = cap>=4 ? (1u << ceil_ilog2(cap * 2)) : 8u;
		
		this->mask = nbuckets - 1u;

		Bucket *p, *pend;
		this->buckets = p = (Bucket *)malloc(nbuckets * sizeof(Bucket));
		pend = p + nbuckets;

		for (; p != pend; ++p)
			p->k = Avail;
	}

	static unsigned hash(int key)//idk what distrib of keys will be
	{
		return ((unsigned)key >> 16u) ^ key;//prob bad
	}

	Bucket* lookup(int key) const
	{
		Bucket *const a = this->buckets;
		const unsigned m = this->mask;

		unsigned pos = hash(key) & m;
		unsigned const startpos = pos;

		for (;;)
		{
			if (a[pos].k == key)
				return a + pos;
			if (a[pos].k == Avail)
				return nullptr;
			//continue on tombstones
			pos = (pos + 1) & m;
			if (pos == startpos)
				return nullptr;
		}
	}

	//returns nullptr if inserted, else ptr to existing entry with same key
	InsertResult insert(int key)
	{
		Bucket *const a = this->buckets;
		const unsigned m = this->mask;

		unsigned pos = hash(key) & m;

		for (;;)
		{
			if (a[pos].k < 0) //a[pos].k == Avail || a[pos].k == Tombstone)
			{
				a[pos].k = key;
				return { a + pos, true };
			}

			if (a[pos].k == key)//existing
				return { a + pos, false };

			pos = (pos + 1) & m;
		}
	}
	
	void remove(Bucket *buck)
	{
		buck->k = Tombstone;
		//printf("removed "); print();
	}
};

class DList
{
	int nfilled = 0; // since no deletion for this, once this hits cap, it stays that. dont need freelist or something
	int cap = 0;//capacity
	int ifirst = -1;//will be set to first when check nFilledNodes == 0
	int ilast = -1; // what a pain, need remember all invariants
	Node *nodes = nullptr;
public:
	~DList()
	{
		free(nodes);
	}

	DList(int c) : cap(c)
	{
		this->nodes = (Node *)malloc(c * sizeof(Node));
	}

	//allocs a new node and sets it to the front of the list. returns ptr to it so caller can set vals after
	//returns nullptr if full
	Node *try_push_front()
	{
		if (nfilled != cap)
		{
			unsigned const iNew = nfilled++;
			Node *const pNew = &nodes[iNew];

			if (iNew == 0)
			{
				ifirst = ilast = iNew;
				pNew->iprev = -1;
				pNew->inext = -1;
			}
			else
			{
				Node *const pOldHead = &nodes[ifirst];
				int const iOldHead = ifirst;
				//set 4 ptrs. since loaded stuff into temps, order not really mater, but should be careful of it

				pOldHead->iprev = iNew;
				pNew->inext = iOldHead;

				pNew->iprev = -1;
				ifirst = iNew;
			}

			return pNew;
		}
		else
			return nullptr;
	}

	void lift_to_front(Node *pB)
	{
		int const a = pB->iprev, c = pB->inext;

		if (a < 0)//if 'b has no prev, it is the head already
		{
			return;
		}
		else//b is not the head, 'a is a valid index
		{
			//1: detatch from list, and fix up ptrs in that area. 
			nodes[a].inext = c;
			if (c >= 0) nodes[c].iprev = a;
			else        ilast = a;//b was the last then, if no valid b.inext

			//2: insert as front of list. 4 ptr assigns to make, 2 per link.
			unsigned const b = int(pB - nodes);

			nodes[ifirst].iprev = b;
			pB->inext = ifirst;

			pB->iprev = -1;
			ifirst = b;
		}
	}

	Node* lift_back_to_front()
	{
		Node *const p = & nodes[ilast];
		lift_to_front(p);//func has branch, know its the tail though.
		return p;
	}

	/*
	void printls()
	{
		if (ifirst < 0) { puts("empty list");  return; };

		int lastoff;
		int off = ifirst;
		for (;;)
		{
			Node node = nodes[off];
			lastoff = off;

			printf(" %d", node.val);
			//getchar();
			off = node.inext;
			if (off < 0)
			{
				assert(lastoff == ilast);
				break;
			}
		}

		putchar('\n');
	}
	*/
};

class LRUCache
{
	HashMap hmap;
	DList ls;
public:
	LRUCache(int c) : hmap(c), ls(c)
	{

	}

	int get(int key)
	{
		Bucket *buck = hmap.lookup(key);

		if (buck != nullptr)
		{
			Node *pN = buck->pNode;
			ls.lift_to_front(pN);
			return pN->val;
		}
		else
			return -1;
	}

	//put(key, value) - Set or insert the value if the key is not already present.
	//When the cache reached its capacity, it should invalidate the least recently used item before inserting a new item.
	void put(int key, int value)
	{
		HashMap::InsertResult res = hmap.insert(key);//@X: can go 1 over cap like this for order, but that okay since hmap buckets is at least *2

		//care, 2 ptr assigns, from bucket to node, and node to bucket.

		if (!res.inserted) // already existed, lift to front and change value
		{
			Node *pNode = res.pBucket->pNode;

			//dont need set res.pBucket->pNode =... here
			pNode->pBucket = res.pBucket;
			
			pNode->val = value;

			ls.lift_to_front(pNode);
			//printf("liftarb "); ls.printls();
		}
		else//inserted into hashmap, need to set some pBucket->pNode=... in all paths here:
		{
			Node *pNode = ls.try_push_front();
			
			bool bpush(pNode != nullptr);

			if (pNode == nullptr)//no room in list, evict
			{
				pNode = ls.lift_back_to_front();
				hmap.remove(pNode->pBucket);
			}

			res.pBucket->pNode = pNode;
			pNode->pBucket = res.pBucket;

			pNode->val = value;

			//printf(bpush?"pushfrn ":"liftlas" ); ls.printls();
		}
	}
};

/*
Input
["LRUCache","put","put","put","put","get","get","get","get","put","get","get","get","get","get"]
[[3],       [1,1],[2,2],[3,3],[4,4],[4],  [3],  [2],  [1],  [5,5],[1],  [2],  [3],  [4],  [5]]
Output
[null,null,null,null,null,4,3,2,-1,null,-1,2,-1,4,5]
*/


//I DID THIS BEFORE IN OS CLASS