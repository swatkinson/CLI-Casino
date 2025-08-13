// CLI Casino | Sebastian Solorzano | CSCN71030(arguably not anymore)
//for ansi escape code stuff. probably ther'ell be no functions?

#pragma once

//values for SGR modes, mainly color. choosing this over #defing them since I love enums
//incomplete list, just add more as you need them (it is trivial to do so)
typedef enum sgrcodes {
	blink = 6,
	blackbg = 40,
	whitebg = 107,

	black = 30,
	red = 31,
	green = 32,
	yellow = 33,
	blue = 34,

	gray = 90,//technically 'bright black' lol
	bred = 91,
	byellow = 93,
	white = 97, //technically bright white, default is grayish

	reset = 0
}COLOR;