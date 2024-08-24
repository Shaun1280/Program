package main

import (
	"fmt"
	"errors"
	"math/rand"
	"time"
)

func doSomething() (float32, error) {
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	tmp := r.Float32()
	if tmp < 0.5 {
		return tmp, errors.New("Error")
	}
	return tmp, nil
}

func main() {
	if value, err := doSomething(); err != nil {
		fmt.Println(value)
		fmt.Println(err)
	} else {
		fmt.Println(value)
		fmt.Println(err)
	}
}