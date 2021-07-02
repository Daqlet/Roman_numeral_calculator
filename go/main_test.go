package main

import (
	"testing"
)

func Test_ConvertToRoman10(t *testing.T) {
	if ConvertToRoman(10) != "X" {
		t.Fail()
	}
}

func Test_ConvertToRoman49(t *testing.T) {
	if ConvertToRoman(49) != "XLIX" {
		t.Fail()
	}
}

func Test_IsCorrectOperation1(t *testing.T) {
	temp := []Node{{1, '0'}, {0, '+'}, {1, '0'}}
	if !IsCorrectOperation(&temp) {
		t.Fail()
	}
}

func Test_IsCorrectOperation2(t *testing.T) {
	temp := []Node{{1, '0'}, {0, '+'}, {1, '+'}}
	if IsCorrectOperation(&temp) {
		t.Fail()
	}
}

func Test_ConvertToRoman20(t *testing.T) {
	if ConvertToFloat([]rune("XX")) != 20 {
		t.Fail()
	}
}

func Test_ConvertToFloat94(t *testing.T) {
	if ConvertToFloat([]rune("XCIV")) != 94 {
		t.Fail()
	}
}

func Test_IsCorrectRomanNumber96_1(t *testing.T) {
	if !IsCorrectRomanNumber([]rune("XCVI")) {
		t.Fail()
	}
}

func Test_IsCorrectRomanNumber96_2(t *testing.T) {
	if IsCorrectRomanNumber([]rune("VCI")) {
		t.Fail()
	}
}

func Test_IsCorrectRomanNumber_incor(t *testing.T) {
	if IsCorrectRomanNumber([]rune("iiv")) {
		t.Fail()
	}
}

func Test_Parse1(t *testing.T) {
	var temp []Node
	if !Parse([]rune("X+I+(II-V/II)*XX-VI"), &temp) {
		t.Fail()
	}
}

func Test_Parse2(t *testing.T) {
	var temp []Node
	if !Parse([]rune("X+I"), &temp) {
		t.Fail()
	}
}

func Test_Combine1(t *testing.T) {
	result, err := Combine(float64(5), float64(6), '+')
	if err != nil || result.value != float64(11) || result.character != '0' {
		t.Fail()
	}
}

func Test_Combine2(t *testing.T) {
	_, err := Combine(float64(5), float64(0), '/')
	if err == nil {
		t.Fail()
	}
}

func Test_CalculateExpr1(t *testing.T) {
	var idx int = 0
	var temp = []Node{
		{5, '0'},
		{0, '+'},
		{0, '('},
		{2, '0'},
		{0, '/'},
		{1, '0'},
		{0, ')'},
	}
	result, err := CalculateExpr(&idx, &temp)
	if err != nil || result != 7 {
		t.Fail()
	}
}

func Test_CalculateExpr2(t *testing.T) {
	var idx int = 0
	var temp = []Node{
		{5, '0'},
		{0, '+'},
		{0, '('},
		{-1, '0'},
		{0, '/'},
		{3, '0'},
		{0, ')'},
	}
	result, err := CalculateExpr(&idx, &temp)
	if err != nil || result != 4 {
		t.Fail()
	}
}

func Test_CalculateExpr3(t *testing.T) {
	var idx int = 0
	var temp = []Node{
		{5, '0'},
		{0, '+'},
		{0, '('},
		{-1, '0'},
		{0, '/'},
		{0, '0'},
		{0, ')'},
	}
	_, err := CalculateExpr(&idx, &temp)
	if err == nil {
		t.Fail()
	}
}
