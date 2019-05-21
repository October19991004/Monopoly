#pragma once
class Object
{
public:
	virtual void start() {};
	virtual void loop() {};
	Object();
	~Object();
};

