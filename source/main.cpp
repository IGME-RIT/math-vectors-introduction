/*
Title: Introduction to Vector Math
File Name: main.cpp
Copyright © 2016
Author: Andrew Litfin
Written under the supervision of David I. Schwartz, Ph.D., and
supported by a professional development seed grant from the B. Thomas
Golisano College of Computing & Information Sciences
(https://www.rit.edu/gccis) at the Rochester Institute of Technology.
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or (at
your option) any later version.
This program is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// The bread and butter of games programming is vector mathematics and linear algebra.
// The vast majority of the mathematics used in games falls under this category,
//  though it is not the only math used (e.g. discrete math, calculus).
// This tutorial series will take you through the basics of vector math.
// Future tutorials in this series will detail other aspects of linear algebra, particularly matrices.
// The exposition follows that of "Foundations of Game Engine Development" (Volume 1),
//  by Eric Lengyel.
// This file provides exposition, definitions, and explanations, and all other files implement vector classes
//  as you would see them in most game engines. The implementations are modeled after those of Eric Lengyel
//  in FGED, Volume 1 and the Tombstone Engine, though they are my own.
// Only Vector2D.h is heavily annotated, the others are mostly identical.

// This tutorial explains the basics of what a vector is and what operations we can use on vectors.
// In the next tutorial, we will discuss the lengths of vectors, and ways to "multiply" vectors, as well as geometric considerations.

#include "../header/helpers.h"
#include "../header/Vector2D.h"
#include "../header/Vector3D.h"
#include "../header/Vector4D.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main()
{
	// Required for the random functions in helpers to work.
	srand(static_cast<unsigned>(time(0)));

	// Almost all quantities arising from geometry and physics that are applied to virtual simulation fall under two categories:
	//  1) Scalars
	//     These are the familiar real numbers.  Scalars are a single quantity representing anything with a magnitude.
	//     For example, mass, distance, time, speed, etc.
	//  2) Vectors
	//     Vectors are quantities that carry enough information to represent not only magnitude, but also direction.
	//     A few examples:
	//     * The difference between two points in space is a vector that tells both which direction you would need to travel
	//        in order to get from one point to the other, but also how far you need to travel.
	//     * The velocity of an object imparts knowledge both about the object's current speed (the magnitude of the velocity)
	//        and its current direction of travel.
	//     * Forces acting on an object have both magnitude and a direction they act on.

	// So what *is* a vector? Unfortunately, the most mathematically accurate answer is just "An element of a vector space."
	//  Not very helpful. If you want to know more about vector spaces, see [math-vector-spaces].

	// Fortunately, in the majority of contexts in games, we are working in the vector space R^n, or the n-dimensional Cartesian space,
	//  in which vectors are easily represented as ordered tuples of real numbers.
	//  e.g. v = (1, 2, 3), where each element represents a distance along one basis axis.
	// As a reminder, Cartesian coordinates are a way to assign a unique representation to every point in n-dimensional space.
	// So this vector v has an x component of 1, a y component of 2, and a z component of 3.
	Vector3D v = Vector3D(1, 2, 3);
	std::cout << "v = " << v << '\n';

	// In games, we are almost always limited to 2 or 3 dimensional space.
	// As such, you would expect the vectors we use to almost always be 2 or 3 dimensional vectors.
	// In 2D, this is the case.
	// However, most of the math done by 3D games is actually in what's called 4D homogeneous space.
	//  It has a fourth component most often used to determine if the vector is a 3D "directional" vector or a 3D "point" vector.
	//  The fourth component can be thought of as the "weight" of the vector, so is often called w.
	//  Unless you really know what you're doing, the w component should always be either 0 (direction) or 1 (point).
	//  As a code consideration, some engines, such as the Tombstone Engine by Eric Lengyel, actually make this distinction
	//   by defining two separate structs for 3D points versus 3D vectors, and define separate operations for each struct.
	//   For example, it does not allow you to add points together, but you can subtract them to get the vector between them.
	//  More on homogeneous spaces in a future tutorial.
	Vector2D twoD = Vector2D(1, 2);
	Vector3D threeD = Vector3D(1, 2, 3);
	Vector4D fourD = Vector4D(1, 2, 3, 1);
	std::cout << "A 2D vector: " << twoD << '\n';
	std::cout << "A 3D vector: " << threeD << '\n';
	std::cout << "A 4D vector: " << fourD << '\n';

	///////////////////////
	// Vector Operations //
	///////////////////////

	// All vector spaces have a minimum of 2 operations that are allowed: Addition and scalar multiplication.
	// Both are conducted component-wise, that is, like components are added together, and the scalar applies uniformly to all elements.
	Vector3D a = Vector3D((float)randInt(-10, 10), (float)randInt(-10, 10), (float)randInt(-10, 10));
	Vector3D b = Vector3D((float)randInt(-10, 10), (float)randInt(-10, 10), (float)randInt(-10, 10));
	Vector3D c = Vector3D((float)randInt(-10, 10), (float)randInt(-10, 10), (float)randInt(-10, 10));
	std::cout << "a = " << a << ", b = " << b << '\n';
	std::cout << "a + b = " << a + b << '\n';
	std::cout << "5c = " << 5.0f * c << '\n';

	// In addition, one of the axioms of vector spaces is that for every vector u, there exists a unique vector -u such that u + (-u) = 0.
	// We can then define subtraction in terms of negation and addition.
	std::cout << "a - b = a + (-b) = " << a - b << '\n';

	// We also often define scalar division as a shorthand for multiplication by the inverse, i.e. v/s = (1/s)v
	std::cout << "c/2 = " << c / 2.0f << '\n';

	// Because addition and scalar multiplication are done component-wise, we then can deduce the following:
	if ((a + b == b + a) /* Addition is commutative */ &&
		((a + b) + c == a + (b + c)) /* Addition is associative */ &&
		((2 * 3)*a == 2 * (3 * a)) /* Scalar multiplication is associative */ &&
		(2 * a == a * 2) /* Scalar multiplication is commutative */ &&
		(5 * (a + b) == 5 * a + 5 * b) /* Scalar multiplication is distributive i*/ &&
		((2 + 3)*a == 2 * a + 3 * a) /* Scalar multiplication is distributive ii */)
	{
		std::cout << "Our rules satisfy the axioms for vector spaces!\n";
	}
	// These are the axioms a vector space must satisfy in order to actually be a vector space.

	std::cout << "Press Enter to continue . . . ";
	std::cin.get();
	return 0;
}
