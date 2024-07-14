package main

import (
	"fmt"
)

func doSomething() error {
	return 1
}

func main() {
	if value, err := doSomething(); err != nil {
		fmt.Println(err)
	}
}