#ifndef __Action__
#define __Action__

enum ROTATIONS {NONE, CLOCKWISE, COUNTER_CLOCKWISE, FLIP};

class Action {
	public:
		Action();
		Action(int rot, int col);
		int rotation, column;
	private:
};

#endif