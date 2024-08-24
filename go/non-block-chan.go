package main

import (
	"fmt"
	"time"
)

func main() {
	// 1. Buffered channel
	bufferedChan := make(chan int, 2)
    bufferedChan <- 1 // Won't block
    bufferedChan <- 2 // Won't block
    // bufferedChan <- 3 // This would block if uncommented

	// 2. Using select to handle multiple channels
	ch1 := make(chan string)
	ch2 := make(chan string)

	go func() {
		time.Sleep(time.Second * 2)
		ch1 <- "Message from ch1"
	}()

	go func() {
		time.Sleep(time.Second)
		ch1 <- "Message from ch2"
	}()

	// Once a case in the select statement is executed
	// the entire select block exits.
	select {
	case msg1 := <-ch1:
		fmt.Println(msg1)
	case msg2 := <-ch2:
		fmt.Println(msg2)
	}

	// 3. Using time.After to avoid permanent blocking
    ch := make(chan string)
    
    go func() {
        time.Sleep(2 * time.Second)
        ch <- "Delayed message"
    }()

	select {
	case msg := <-ch:
		fmt.Println(msg)
	case <-time.After(1 * time.Second):
		fmt.Println("Timeout")
	}

	// 4. Using default case in select for non-blocking operations
    ch3 := make(chan int)
    
    select {
    case x := <-ch3:
        fmt.Println("Received from ch3: ", x)
    default:
        fmt.Println("No value received, continuing execution")
    }
}