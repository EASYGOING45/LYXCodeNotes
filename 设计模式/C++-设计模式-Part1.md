# C++-设计模式-Part1

## 单例（Singleton）模式

- 有些时候，我们需要整个程序中有且只有一个实例
- 常见场景：如系统日志，Windoiws资源管理窗口，数据库分配主键操作等
- 实现思路：
  - Singleton拥有一个私有构造函数，确保用户无法通过new直接实例它
  - 包含一个静态私有成员变量instance与静态公有方法Instance()

```C++
//Singleton.h
class Singleton
{
public:
	static const Singleton* getInstance();
	static void DoSomething()
	{
		cout << "Do Something" << endl;
	}
// 将构造和析构函数私有化，防止外部访问
private:
	Singleton();
	~Singleton();

	static Singleton* This; // 使用静态变量帮助解决资源的分配和释放
};
```

```C++
Singleton* Singleton::This = nullptr;
const Singleton* Singleton::getInstance()
{
	if (!This)
	{
		cout << "创建实例" << endl;
		This = new Singleton;
	}
	return This;
}

Singleton::Singleton()
{
}

Singleton::~Singleton()
{
}
```

![image-20230105152249326](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105152249326.png)

## 观察者（Observer）模式

- 在观察者模式中，观察者需要直接订阅目标事件；
- 在目标发出内容改变的事件后，直接接收事件并做出响应，对象常是一对多关系
- 常见场景：各种MVC框架中，Model的变化通知各种类型的view时几乎都存在这种模式
- 实现思路
  - 将问题的职责解耦合（让不同的类去处理不同的事情）
  - 将Observable和Observer抽象开，分清抽象和实体

```C++
/*观察者类*/
class Observer
{
public:
	Observer() { ; }
	virtual ~Observer() { ; }

	// 当被观察对象发生变化时，通知被观察者调用这个方法
	virtual void Update(void* pArg) = 0;	//纯虚函数
};
```

```C++
class Observerable
{
public:
	Observerable();
	virtual ~Observerable();

	// 注册观察者
	void Attach(Observer* pOb);

	// 反注册观察者
	void Detach(Observer* pOb);

	int GetObseverCount() const
	{
		return _Obs.size();
	}

	void DetachAll()
	{
		_Obs.clear();
	}

	virtual void GetSomeNews(string str)
	{
		SetChange(str);
	}
protected:
	void  SetChange(string news);   // 有变化，需要通知

private:
	void Notify(void* pArg);

private:
	bool _bChange;	//标志：当前状态是否有变化
	list<Observer*> _Obs;	//观察者清单 （list）链表
};
```

```C++
// 注册观察者
void Observerable::Attach(Observer* pOb)
{
	if (pOb == NULL)
	{
		return;
	}

	// 看看当前列表中是否有这个观察者
	auto it = _Obs.begin();
	for (; it != _Obs.end(); it++)
	{
		if (*it == pOb)
		{
			return;
		}
	}

	_Obs.push_back(pOb);
}

// 反注册观察者  注销
void Observerable::Detach(Observer* pOb)
{
	if ((pOb == NULL) || (_Obs.empty() == true))
	{
		return;
	}

	_Obs.remove(pOb);
}

void Observerable::SetChange(string news)
{
	_bChange = true;

	Notify( ( (void*)news.c_str() ));
}


void Observerable::Notify(void* pArg)
{
	if (_bChange == false)
	{
		return;
	}

	// 看看当前列表中是否有这个观察者
	auto it = _Obs.begin();
	for (; it != _Obs.end(); it++)
	{
		(*it)->Update(pArg);
	}

	_bChange = false;
}
```



```C++
class News : public Observerable
{
public:
	virtual void GetSomeNews(string str)
	{
		SetChange("News: " + str);
	}
};

/*观察者1*/
class User1:public Observer
{
public:
	virtual void Update(void* pArg)	//重写update方法
	{
		cout << "User1 Got News: " << reinterpret_cast<char*>(pArg) <<endl;
	}
};
/*观察者2*/
class User2 :public Observer
{
public:
	virtual void Update(void* pArg)
	{
		cout << "User2 Got News: " << reinterpret_cast<char*>(pArg) <<endl;
	}
};

int main()	
{
	User1 u1;
	User2 u2;

	News n1;
	n1.GetSomeNews("T00");
	cout << "当前观察者数量：";
	cout << n1.GetObseverCount() << endl;  // 0

	n1.Attach(&u1);
	n1.Attach(&u2);
	n1.GetSomeNews("T11");
	cout << "当前观察者数量：";
	cout << n1.GetObseverCount() << endl;  // 2

	n1.Detach(&u2);
	n1.GetSomeNews("T22");
	cout << "当前观察者数量：";
	cout << n1.GetObseverCount() << endl;  // 1

	n1.DetachAll();
	n1.GetSomeNews("T33");
	cout << "当前观察者数量：";
	cout << n1.GetObseverCount() << endl;  // 0

    return 0;
}
```

![image-20230105155526799](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105155526799.png)

## 适配器（Adapter）模式

- 适配器将类接口转换为客户端期望的另一个接口
- 使用适配器可以防止类由于接口不兼容而一起工作
- 适配器模式的动机是：如果可以更改接口，则可以重用现有软件
- 尽量不更改原有代码，而是用适配器来进行继承复写

基本类：

```C++
class LegacyRectangle
{
public:
	LegacyRectangle(double x1, double y1, double x2, double y2)
	{
		_x1 = x1;
		_y1 = y1;
		_x2 = x2;
		_y2 = y2;
	}

	void LegacyDraw()
	{
		cout << "LegacyRectangle:: LegacyDraw()" << _x1 << " " << _y1 << " " << _x2 << " " << _y2 << endl;
	}

private:
	double _x1;
	double _y1;
	double _x2;
	double _y2;
};

class Rectangle
{
public:
	virtual void Draw(string str) = 0;
};
```

第一种适配方式：使用多重继承：

```C++

// 第一种适配的方式：使用多重继承
class RectangleAdapter: public Rectangle, public LegacyRectangle
{
public:
	RectangleAdapter(double x, double y, double w, double h) :
		LegacyRectangle(x, y, x + w, y + h)
	{
		cout << "RectangleAdapter(int x, int y, int w, int h)" << endl;
	}

	virtual void Draw(string str)
	{
		cout << "RectangleAdapter::Draw()" << endl;
		LegacyDraw();
	}
};
```

![image-20230105163740350](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105163740350.png)

第二种适配方式：组合方式

![image-20230105163826074](https://happygoing.oss-cn-beijing.aliyuncs.com/img/image-20230105163826074.png)

## 设计模式小结

- 23种面向对象的设计模式从分类上大致有创建型、结构型和行为型模式
- 设计模式不是万能的，它建立在系统变化点上，哪里有变化哪里就可以用
- 设计模式为了解耦合，为了扩展，它通常是演变过来的，需要演变才能准确定位
- 设计模式是一种软件设计的方法，不是标准，目前大部分的框架中都已经包含了大量设计模式的思想