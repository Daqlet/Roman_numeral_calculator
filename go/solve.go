package main

import (
	"bufio"
	"fmt"
	"io"
	"strings"
)

func RunConverter(reader io.Reader) {
	scanner := bufio.NewScanner(reader)
	for scanner.Scan() {
		Solve(scanner.Text())
	}
}

func Solve(task string) {
	parsedExpr := make([]Node, 0)
	task = strings.ReplaceAll(task, " ", "")
	if Parse([]rune(task), &parsedExpr) {
		idx := 0
		answer, err := CalculateExpr(&idx, &parsedExpr)
		if err != nil {
			fmt.Println(err)
			return
		}
		fmt.Println(ConvertToRoman(answer))
	} else {
		fmt.Println("error: wrong input format")
	}
}
