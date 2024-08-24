package main

import "fmt"

func example() {
	for i := 0; i < 5; i++ {
		defer func() {
			fmt.Println(i) // in closure, i is reference 
		}()
	}
}

func main() {
	example()
}