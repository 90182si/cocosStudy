#ifndef __QUAD_TREE_H__
#define __QUAD_TREE_H__

#include "cocos2d.h"
#include <vector>


namespace GameTool {

	template <typename T>
	struct QuadNode 
	{
		size_t m_depth;
		int index;
		//std::vector<T> m_nodes;
		QuadNode* m_pChild[4];
		cocos2d::Rect m_rect;
		std::array<cocos2d::Rect, 4> m_rChild;
		void init1()
		{
			for (int i = 0; i < 4; i++)
			{
				m_pChild[i] = NULL;
			}
			index = -1;
		}
		void init2(cocos2d::Rect rect)
		{
			m_depth = (int)log2(rect.size.width);
			m_rect = rect;
			m_rChild = {
				cocos2d::Rect(rect.origin,rect.size / 2),
				cocos2d::Rect({rect.origin.x + rect.size.width / 2,rect.origin.y},rect.size / 2),
				cocos2d::Rect({rect.origin.x,rect.origin.y + rect.size.height / 2},rect.size / 2),
				cocos2d::Rect({rect.origin.x + rect.size.width / 2,rect.origin.y + rect.size.height / 2},rect.size / 2)
			};
		}
		//判断矩形包含矩形(A包含B ?)
		bool containsRect(cocos2d::Rect A, cocos2d::Rect B)
		{
			return (A.origin.x <= B.origin.x + B.size.width) && (A.origin.x + A.size.width > B.origin.x) &&
				(A.origin.y <= B.origin.y + B.size.height) && (A.origin.y + A.size.height > B.origin.y);
		}
		//判断放置位置位置
		int calRectPos(cocos2d::Rect rect)
		{
			if (containsRect(m_rect, rect))
			{
				for (int i = 0; i < 4; i++)
				{
					if (containsRect(m_rChild[i], rect))
					{
						return i;
					}
				}
				return -1;
			}
			return -2;
		}
	};

	template <typename T>
	class StaticQuadTree
	{
	private:
		
		std::vector<T> m_nodes;
	public:
		QuadNode<T>* quadTree;
		StaticQuadTree()
		{
			quadTree = (QuadNode<T>*)malloc(sizeof(QuadNode<T>));
			quadTree->init1();
		}

		void addPoint(QuadNode<T>* head, T data, cocos2d::Point point)
		{
			if (head->m_depth == 0)
			{
				m_nodes.push_back(data);
				head->index = m_nodes.size() - 1;
			}
			else
			{
				for (int i = 0; i < 4; i++)
				{
					if (head->m_rChild[i].containsPoint(point))
					{
						if (head->m_pChild[i] == NULL)
						{
							head->m_pChild[i] = (QuadNode<T>*)malloc(sizeof(QuadNode<T>));
							head->m_pChild[i]->init1();
							head->m_pChild[i]->init2(head->m_rChild[i]);
						}
						addPoint(head->m_pChild[i], data, point);
						return;
					}
				}
			}
		}
		//起点为左上角
		void addNode(QuadNode<T>*& head, T data, cocos2d::Point point)
		{
			if (head == NULL)
			{
				head = (QuadNode<T>*)malloc(sizeof(QuadNode<T>));
				head->init1();
			}
			if (m_nodes.size() == 0)
			{
				cocos2d::Point center(0, 0);
				//计算矩形区域整个大小
				int v = point.x - center.x > point.y - center.y ? point.x - center.x : point.y - center.y;
				int n = log2(v) + 1;
				int wid = pow(2,n);
				cocos2d::Rect rect(center, cocos2d::Size(wid, wid));
				head->init2(rect);

				addPoint(head, data, point);
			}
			else
			{
				while (!head->m_rect.containsPoint(point))
				{
					QuadNode<T>* newP = (QuadNode<T>*)malloc(sizeof(QuadNode<T>));
					newP->init1();
					cocos2d::Rect bigRect;
					bigRect.size = head->m_rect.size * 2;
					// x|
					// ---
					//  |
					if (point.x < head->m_rect.origin.x && point.y > head->m_rect.origin.y+ head->m_rect.size.height)
					{
						bigRect.origin.x = head->m_rect.origin.x - head->m_rect.size.width;
						bigRect.origin.y = head->m_rect.origin.y;
						newP->m_pChild[1] = head;
					}
					//  |x
					// ---
					//  |
					else if (point.x >= head->m_rect.origin.x && point.y >= head->m_rect.origin.y)
					{
						bigRect.origin = head->m_rect.origin;
						newP->m_pChild[0] = head;
					}
					//  |
					// ---
					// x|
					else if (point.x < head->m_rect.origin.x+head->m_rect.size.width && 
						point.y < head->m_rect.origin.y + head->m_rect.size.height)
					{
						bigRect.origin.x = head->m_rect.origin.x - head->m_rect.size.width;
						bigRect.origin.y = head->m_rect.origin.y - head->m_rect.size.height;
						newP->m_pChild[3] = head;
					}
					//  |
					// ---
					//  |x
					else if (point.x >= head->m_rect.origin.x && point.y < head->m_rect.origin.y)
					{
						bigRect.origin.x = head->m_rect.origin.x - head->m_rect.size.width;
						bigRect.origin.y = head->m_rect.origin.y;
						newP->m_pChild[2] = head;
					}
					newP->init2(bigRect);
					head = newP;
				}

				addPoint(head, data, point);
			}
			
			
		}

		bool isEmpty(QuadNode<T>*& head, cocos2d::Point point)
		{
			if (m_nodes.size() > 0)
			{
				if (head->m_depth == 0)
				{
					if (head->index == -1)
					{
						return true;
					}
					else return false;
				}
				else
				{
					for (int i = 0; i < 4; i++)
					{
						if (head->m_rChild[i].containsPoint(point))
						{
							if (head->m_pChild[i] == NULL)
							{
								return true;
							}
							return isEmpty(head->m_pChild[i], point);
						}
					}
					return true;
				}
			}
			else return true;
		}

		void move(T data, cocos2d::Point point)
		{

		}
		~StaticQuadTree() {}

	public:

	private:


	};
}

namespace GameToolV_1 {
	struct Point {
		float x, y;
		Point(float x, float y) {
			this->x = x;
			this->y = y;
		}
	};
	struct Rect {
		float x, y;
		float width, height;
		Rect() {}
		Rect(float x, float y, float width, float height) {
			this->x = x;
			this->y = y;
			this->width = width;
			this->height = height;
		}
		Rect& operator =(const Rect r) {
			x = r.x;
			y = r.y;
			width = r.width;
			height = r.height;
			return *this;
		}
		//B包含于A?
		bool containsRect(Rect B) {
			return (B.x >= x) && (B.x + B.width < x + width) && 
				   (B.y >= y) && (B.y + B.height < y + height);
		}
		bool containsRectB(Rect B) {
			return (B.x >= x) && (B.x + B.width <= x + width) &&
				(B.y >= y) && (B.y + B.height <= y + height);
		}
		bool containsPoint(Point B) {
			return (B.x >= x) && (B.x < x + width) &&
				(B.y >= y) && (B.y < y + height);
		}
		bool containsPointB(Point B) {
			return (B.x > x) && (B.x < x + width) &&
				(B.y > y) && (B.y < y + height);
		}
		Point center() {
			return Point(x + width / 2, y + height/2);
		}
	};
	template <typename T>
	struct nodeData {
		T node;
		Rect rect;
	};
	template <typename T>
	class QuadNode {
	public:
		//T* t;                                  //数据指针  
		Rect m_rect;                           //自己的区域
		Rect m_bigRect;                        //自己的区域        
		std::array<QuadNode<T>*, 4>  m_pChild; //四个子节点
		std::array<Rect, 4> m_rChild;          //子区域    
		size_t m_level;
		std::list<T> m_child;
		//std::list<Rect> m_childRect;
		std::map<T,Rect> m_childRectMap;

		QuadNode<T>* m_par;
		UCHAR childID;
		int m_allChildCount = 0;
	public:
		QuadNode() {
			childID = -1;
			m_level = 0;
			m_par = NULL;
			//t = nullptr;
			m_pChild = {
				NULL;
				NULL;
				NULL;
				NULL;
			};
			m_rChild = {
				Rect(0, 0, 0, 0);
				Rect(0, 0, 0, 0);
				Rect(0, 0, 0, 0);
				Rect(0, 0, 0, 0);
			};
		}
		//边长
		QuadNode(Rect rect) {
			childID = -1;
			m_level = 0;
			m_par = NULL;
			//t = nullptr;
			m_rect = rect;
			m_pChild = {
				NULL,
				NULL,
				NULL,
				NULL
			};
			m_rChild = {
				Rect(rect.x,rect.y,rect.width / 2,rect.height / 2),
				Rect(rect.x + rect.width / 2,rect.y,rect.width / 2,rect.height / 2),
				Rect(rect.x,rect.y + rect.height / 2,rect.width / 2,rect.height / 2),
				Rect(rect.x + rect.width / 2,rect.y + rect.height / 2,rect.width / 2,rect.height / 2)
			};
		}

	};

	template <typename T>
	class QuadTree {
	private:
		QuadNode<T> *m_quadTree;
		std::map<T, QuadNode<T>*> m_tdMap;
		int newCount = 0;
		int deleteCount = 0;
	public:
		QuadTree() {
			m_quadTree = NULL;
		}
		void f_addNode(QuadNode<T>*& head, T node, Rect rect) {
			if (head == NULL) {

				float length = 1;
				int level = 0;
				while (length < std::max(rect.width, rect.height)) {
					length *= 2;
					level++;
				}

				head = new QuadNode<T>(Rect(rect.x, rect.y, length, length));
				head->m_level = level;

				head->m_child.push_back(node);
				//head->m_childRect.push_back(rect);
				head->m_childRectMap.insert(std::pair<T, Rect>(node, rect));
				m_tdMap.insert(std::pair<T, QuadNode<T>*>(node, head));
				head->m_allChildCount++;
				//head->m_indexList.push_back(4);
			}
			else {
				Point center = rect.center();
				//如果新加入的rect中心在m_rect中
				if (head->m_rect.containsPoint(center)) {
					//判断在哪个区域
					int i = 0;
					for (; i < 4; i++) {
						if (head->m_rChild[i].containsRectB(rect)) {
							if (head->m_pChild[i] == NULL) {
								head->m_pChild[i] = new QuadNode<T>(head->m_rChild[i]);
								//cocos2d::log("new:%d",newCount++);
								head->m_pChild[i]->m_par = head;
								head->m_pChild[i]->childID = i;
							}
							//head->m_indexList.push_back(i);
							f_addNode(head->m_pChild[i], node, rect);
							head->m_allChildCount++;
							break;
						}
					}
					//不去子区域，在本层
					if (i == 4)
					{
						head->m_child.push_back(node);
						//head->m_childRect.push_back(rect);
						head->m_childRectMap.insert(std::pair<T, Rect>(node, rect));
						m_tdMap.insert(std::pair<T, QuadNode<T>*>(node, head));
						head->m_allChildCount++;
						//head->m_indexList.push_back(4);
					}
				}
				else {
					// 2 3
					// 0 1
					Rect newRect(0, 0, head->m_rect.width * 2, head->m_rect.height * 2);
					if (center.y >= head->m_rect.y + head->m_rect.height && center.x < head->m_rect.x + head->m_rect.width) {
						newRect.x = head->m_rect.x - head->m_rect.width;
						newRect.y = head->m_rect.y;
						QuadNode<T>* newHead = new QuadNode<T>(newRect);
						//cocos2d::log("new:%d", newCount++);
						newHead->m_pChild[1] = head;
						head->childID = 1;
						head->m_par = newHead;
						head = newHead;

					}
					else if (center.y >= head->m_rect.y && center.x >= head->m_rect.x + head->m_rect.width) {
						newRect.x = head->m_rect.x;
						newRect.y = head->m_rect.y;
						QuadNode<T>* newHead = new QuadNode<T>(newRect);
						//cocos2d::log("new:%d", newCount++);
						newHead->m_pChild[0] = head;
						head->childID = 0;
						head->m_par = newHead;
						head = newHead;
					}
					else if (center.y < head->m_rect.y && center.x >= head->m_rect.x) {
						newRect.x = head->m_rect.x;
						newRect.y = head->m_rect.y - head->m_rect.height;
						QuadNode<T>* newHead = new QuadNode<T>(newRect);
						//cocos2d::log("new:%d", newCount++);
						newHead->m_pChild[2] = head;
						head->childID = 2;
						head->m_par = newHead;
						head = newHead;
					}
					else if (center.y < head->m_rect.y + head->m_rect.height && center.x < head->m_rect.x) {
						newRect.x = head->m_rect.x - head->m_rect.width;
						newRect.y = head->m_rect.y - head->m_rect.height;
						QuadNode<T>* newHead = new QuadNode<T>(newRect);
						//cocos2d::log("new:%d", newCount++);
						newHead->m_pChild[3] = head;
						head->childID = 3;
						head->m_par = newHead;
						head = newHead;
					}
					f_addNode(head, node, rect);
				}
			}
		}
		void addNode(T node, Rect rect) {
			//clock_t a = clock();
			f_addNode(m_quadTree, node, rect);
			//log("addNode:%d", clock() - a);
		}		
		void thrownNode(T node) {
			auto iter = m_tdMap.find(node);
			if (iter != m_tdMap.end()) {
				iter->second->m_child.remove(node);
				QuadNode<T>* par = iter->second;
				auto iter2 = par->m_childRectMap.find(node);
				par->m_childRectMap.erase(iter2);
				
				QuadNode<T>* par0;
				do {
					par0 = par->m_par;
					par->m_allChildCount--;
					//par0->m_allChildCount--;

					par = par0;
				} while (par != NULL);
				m_tdMap.erase(iter);
			}
		}
		void f_clearup(QuadNode<T>*& head) {
			int i = 0,j = 0;
			for (; i < 4; i++) {
				if (head->m_pChild[i] != NULL) {
					f_clearup(head->m_pChild[i]);
				}
			}
			for (; j < 4; j++) {
				if (head->m_pChild[j] != NULL) {
					break;
				}
			}
			if (j == 4) {
				if (head->m_child.size() == 0) {
					delete head;
					head = NULL;
				}
			}
		}
		void clearup() {
			f_clearup(m_quadTree);
		}
		bool f_isEmpty(QuadNode<T>* head, Point point) {
			if (head == NULL) {
				return true;
			}
			//if (head->m_childRectMap.size() != 0) 
			{
				for (auto rect : head->m_childRectMap) {
					if (rect.second.containsPointB(point)) {
						return false;
					}
				}
			/*}
			else {*/
				int i = 0;
				for (; i < 4; i++) {
					if (head->m_rChild[i].containsPoint(point)) {
						if (head->m_pChild[i] == NULL) {
							return true;
						}
						if (head->m_pChild[i]->m_allChildCount == 0 || f_isEmpty(head->m_pChild[i], point) == false) {
							return false;
						}
					}
					//if (head->m_pChild[i] != NULL) 
					/*{
						if (f_isEmpty(head->m_pChild[i], point) == false) {
							return false;
						}
					}*/
				}
				if (i == 4) {
					return true;
				}
			}
			return true;
		};
		bool isEmpty(Point point) {
			/*auto f_isEmpty = [=](QuadNode<T>* head, Point point)->bool{
				if (head == NULL) {
					return false;
				}
				if (head->m_childRect.size() != 0) {
					for (auto rect : head->m_childRect) {
						if (rect.containsPoint(point)) {
							return true;
						}
					}
				}
				else {
					int i = 0;
					for (; i < 4; i++) {
						if (head->m_pChild[i] != NULL) {
							if (f_isEmpty(head->m_pChild[i], point) == true) {
								return true;
							}
						}
					}
					if (i == 4) {
						return false;
					}
				}
			};*/
			//clock_t a = clock();
			//bool ok = f_isEmpty(m_quadTree, point);
			//log("isEmpty:%d", clock()-a);
			return f_isEmpty(m_quadTree, point);
		}
		bool isEmpty(Rect rect) {
			return f_isEmpty(m_quadTree, Point(rect.x, rect.y)) && f_isEmpty(m_quadTree, Point(rect.x + rect.width, rect.y)) &&
				f_isEmpty(m_quadTree, Point(rect.x, rect.y + rect.height)) && f_isEmpty(m_quadTree, Point(rect.x + rect.width, rect.y + rect.height));
		}
		bool isEmptyExR(Rect rect, T node) {
			auto iter = m_tdMap.find(node);
			if (iter != m_tdMap.end()) {
				std::array<Point, 4> rectPoint{
					Point(rect.x, rect.y),
					Point(rect.x + rect.width, rect.y),
					Point(rect.x, rect.y + rect.height),
					Point(rect.x + rect.width, rect.y + rect.height)
				};
				for (int i = 0; i < 4; i++) {
					if (iter->second->m_rect.containsPoint(rectPoint[i]) == false) {
						if (f_isEmpty(m_quadTree, rectPoint[i]) == false) {
							return false;
						}
					}
				}
			}
			return true;
		}

		std::vector<Rect> m_rects;
		void f_getAllRect(QuadNode<T>* head) {
			m_rects.push_back(head->m_rect);
			for (int i = 0; i < 4; i++) {
				if (head->m_pChild[i] != NULL) {
					f_getAllRect(head->m_pChild[i]);
				}
			}
		}
		void getAllRect() {
			m_rects.clear();
			f_getAllRect(m_quadTree);
		}
	};
}
#endif // __QUAD_TREE_H__