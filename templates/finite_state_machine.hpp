class ProgramState;

class Program {
public:
	Program();
	inline ProgramState* getCurrentState() const { return currentState; }
	void toggle();
	void setState(ProgramState& newState);

private:
	ProgramState* currentState;
};





class ProgramState {
public:
	virtual void enter(Program* program) = 0;
	virtual void toggle(Program* program) = 0;
	virtual void exit(Program* program) = 0;
	virtual ~ProgramState() {}
};





class State1 : public ProgramState {
public:
	void enter(Program* program) {}
	void toggle(Program* program);
	void exit(Program* program) {}
	static ProgramState& getInstance();

private:
	State1() {}
	State1(const State1& other);
	State1& operator=(const State1& other);
};

ProgramState& State1::getInstance()
{
	static State1 singleton;
	return singleton;
}

class State2 : public ProgramState {
public:
	void enter(Program* program) {}
	void toggle(Program* program);
	void exit(Program* program) {}
	static ProgramState& getInstance();

private:
	State2() {}
	State2(const State2& other);
	State2& operator=(const State2& other);
};

ProgramState& State2::getInstance()
{
	static State2 singleton;
	return singleton;
}

class State3 : public ProgramState {
public:
	void enter(Program* program) {}
	void toggle(Program* program);
	void exit(Program* program) {}
	static ProgramState& getInstance();

private:
	State3() {}
	State3(const State3& other);
	State3& operator=(const State3& other);
};

ProgramState& State3::getInstance()
{
	static State3 singleton;
	return singleton;
}





void State1::toggle(Program* program) {
	// State1 -> State2
	program->setState(State2::getInstance());
}

void State2::toggle(Program* program) {
	// State2 -> State3
	program->setState(State3::getInstance());
}

void State3::toggle(Program* program) {
	// State3 -> State1
	program->setState(State1::getInstance());
}





Program::Program()
{
	currentState = &State1::getInstance();
}

void Program::setState(ProgramState& newState)
{
	currentState->exit(this);
	currentState = &newState;
	currentState->enter(this);
}

void Program::toggle()
{
	currentState->toggle(this);
}