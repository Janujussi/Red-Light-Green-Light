// FILE: SegmentDisplay.cpp
//	Implementation of SegmentDisplay.h
//
// Author: Jan Morrison

#include "Arduino.h"
#include "SegmentDisplay.h"

SegmentDisplay::SegmentDisplay()
{
	this->a = 0;
	this->b = 0;
	this->c = 0;
	this->d = 0;
	this->e = 0;
	this->f = 0;
	this->g = 0;

	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
}

SegmentDisplay::SegmentDisplay(int pinA, int pinB, int pinC, int pinD, int pinE, int pinF, int pinG)
{
	this->a = pinA;
	this->b = pinB;
	this->c = pinC;
	this->d = pinD;
	this->e = pinE;
	this->f = pinF;
	this->g = pinG;

	pinMode(a, OUTPUT);
	pinMode(b, OUTPUT);
	pinMode(c, OUTPUT);
	pinMode(d, OUTPUT);
	pinMode(e, OUTPUT);
	pinMode(f, OUTPUT);
	pinMode(g, OUTPUT);
}

SegmentDisplay::~SegmentDisplay()
{
	this->a = 0;
	this->b = 0;
	this->c = 0;
	this->d = 0;
	this->e = 0;
	this->f = 0;
	this->g = 0;
}

void SegmentDisplay::zero()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, HIGH);

	this->currentState = 0;
}

void SegmentDisplay::one()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);

	this->currentState = 1;
}

void SegmentDisplay::two()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, HIGH);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, HIGH);
	digitalWrite(g, LOW);

	this->currentState = 2;
}

void SegmentDisplay::three()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, LOW);

	this->currentState = 3;
}

void SegmentDisplay::four()
{
	digitalWrite(a, HIGH);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);

	this->currentState = 4;
}

void SegmentDisplay::five()
{
	digitalWrite(a, LOW);
	digitalWrite(b, HIGH);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, HIGH);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);

	this->currentState = 5;
}

void SegmentDisplay::six()
{
	digitalWrite(a, LOW);
	digitalWrite(b, HIGH);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);

	this->currentState = 6;
}

void SegmentDisplay::seven()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, HIGH);
	digitalWrite(g, HIGH);

	this->currentState = 7;
}

void SegmentDisplay::eight()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, LOW);
	digitalWrite(e, LOW);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);

	this->currentState = 8;
}

void SegmentDisplay::nine()
{
	digitalWrite(a, LOW);
	digitalWrite(b, LOW);
	digitalWrite(c, LOW);
	digitalWrite(d, HIGH);
	digitalWrite(e, HIGH);
	digitalWrite(f, LOW);
	digitalWrite(g, LOW);

	this->currentState = 9;
}

int SegmentDisplay::getNumber()
{
	return this->currentState;
}