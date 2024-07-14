package main

import (
	"fmt"
)

func modify(slice []int) {
	slice[0] = 100
}

func main() {
	slice := []int{1, 2, 3, 4}
	modify(slice)
	fmt.Println(slice)
}