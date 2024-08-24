package main

import "fmt"

func example() {
	defer func() {
		if r := recover(); r != nil {
			fmt.Println("Recovered:", r)
		}
	}()
	panic("Panic!")
}

func main() {
	example()
}