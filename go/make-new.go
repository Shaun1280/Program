package main

import (
	"fmt"
	"unsafe"
)

type MySlice struct {
	array unsafe.Pointer
	len int
	cap int
}

func main() {
	slice := make([]int, 10, 20) // 20 is capacity
	for i := range slice {
		slice[i] = i
	}

	mymap := make(map[string]int)

	channel := make(chan int)


	mymap["key"] = 42
	slice[1] = 7
	
	go func(ch chan int) {
		println(<-ch)
	}(channel) // should first be ready to receive

	channel <- 8

	println(mymap["key"])
	for i, v := range slice {
		println(i, v)
	}
	println(slice)

	// allocate a new int (return a pointer to the int)
	ptr := new(int)
	*ptr = 42
	println(*ptr)

	slice = append(slice, 42)
	anotherSlice := []int{6, 7, 8}
	fmt.Println(slice)
	slice = append(slice, anotherSlice...)
	fmt.Println(slice)

	copySlice := append(make([]int, 0), slice...)
	copySlice = append([]int(nil), slice...)
	copySlice[0] = 100
	fmt.Println(slice, copySlice)
}