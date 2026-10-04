#pragma once

#include <yuan_window.h>

namespace stickman {

	class MainWindow : public yuanGL::YuanWindow {
	public:
		MainWindow();

	private:
		
		virtual void inloop() override;
	};

}
