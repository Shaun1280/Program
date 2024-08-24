package main

import (
	"fmt"
	"sync"
	"time"
)

var counter int
var mu sync.Mutex

func main() {
	var wg sync.WaitGroup
	wg.Add(1)

	go func() {
		defer wg.Done()
		
		mu.Lock()
		counter++
		mu.Unlock()
		fmt.Println("First goroutine")
	}()

	wg.Wait()

	fmt.Println("Main goroutine")


	quit := make(chan bool)

	go func() {
		fmt.Println("First goroutine")
		time.Sleep(time.Second * 2)
		quit <-true
	}()

	
	fmt.Println(<-quit, "Main goroutine exiting...")
}