package main

import (
	"math"
	"regexp"
)

var mapRoman = map[rune]int{
	'M': 1000,
	'D': 500,
	'C': 100,
	'L': 50,
	'X': 10,
	'V': 5,
	'I': 1,
	'Z': 0,
}
var values = []int{1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1}
var romans = []string{"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"}

func ConvertToRoman(value float64) string {
	temp := int(math.Floor(value))
	if temp == 0 {
		return "Z"
	}
	result := ""
	if temp < 0 {
		temp *= -1
		result = "-"
	}
	for i := 0; i < 13; i++ {
		for temp-values[i] >= 0 {
			result += romans[i]
			temp -= values[i]
		}
	}
	return result
}

func IsOperation(c rune) bool {
	return c == '+' || c == '-' || c == '*' || c == '/'
}

func IsCorrectOperation(parsedExpr *[]Node) bool {
	needOperation := false
	scopeCount := 0
	for i := 0; i < len(*parsedExpr); i++ {
		if (*parsedExpr)[i].character == '(' {
			scopeCount++
			continue
		} else if (*parsedExpr)[i].character == ')' {
			scopeCount--
			if scopeCount < 0 {
				return false
			}
			continue
		}
		if needOperation != IsOperation((*parsedExpr)[i].character) {
			return false
		}
		needOperation = !needOperation
	}
	return scopeCount == 0
}

func ConvertToFloat(roman []rune) int {
	result := 0
	for i := 0; i < len(roman); i++ {
		if i+1 < len(roman) && mapRoman[roman[i]] < mapRoman[roman[i+1]] {
			result += mapRoman[roman[i+1]] - mapRoman[roman[i]]
			i++
		} else {
			result += mapRoman[roman[i]]
		}
	}
	return result
}

func IsCorrectRomanNumber(roman []rune) bool {
	if len(roman) == 1 && roman[0] == 'Z' {
		return true
	}
	romanExpr := "^M{0,4}(CM|CD|D?C{0,3})(XC|XL|L?X{0,3})(IX|IV|V?I{0,3})$"
	ok, err := regexp.Match(romanExpr, []byte(string(roman)))
	if err != nil {
		panic(err)
	}
	return ok && len(roman) > 0
}

func Parse(task []rune, parsedExpr *[]Node) bool {
	needOperation := false
	for i := 0; i < len(task); {
		if task[i] == ')' || task[i] == '(' {
			*parsedExpr = append(*parsedExpr, Node{0, task[i]})
			i++
			continue
		}
		if needOperation {
			*parsedExpr = append(*parsedExpr, Node{0, task[i]})
			i++
			needOperation = false
			continue
		}
		sign := 1
		if task[i] == '-' {
			i++
			sign = -1
		}
		start := i
		for i < len(task) {
			if _, ok := mapRoman[task[i]]; !ok {
				break
			}
			i++
		}
		romanNumber := task[start:i]
		if IsCorrectRomanNumber(romanNumber) {
			value := sign * ConvertToFloat(romanNumber)
			*parsedExpr = append(*parsedExpr, Node{float64(value), '0'})
		} else {
			return false
		}
		needOperation = true
	}
	return IsCorrectOperation(parsedExpr)
}
