#pragma once
#include <iostream>
#include "bintree.h"
#define nodo bintree<int>::node
bintree<int>::node siguiente_inorden(bintree<int>::node n) {
	if (n.null()) {
		return n;
	}
	if (!n.right().null()) {
		n = n.right();
		while (!n.left().null()) {
			n = n.left();
		}
	}
	else {
		while (!n.parent().null() && n.parent().right() == n)
			n = n.parent();
		n = n.parent();
	}
	return n;
}
