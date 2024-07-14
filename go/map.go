package main

import (
	"fmt"
	"sort"
	"sync"
)

func main() {
	myMap := map[string]int{
		"apple":  5,
		"banana": 3,
		"orange": 7,
		"grape":  1,
	}
	keys := []string(nil) // or make([]string, 0, len(myMap))
	for key := range myMap {
		keys = append(keys, key)
	}
	sort.Strings(keys)
	for _, key := range keys {
		fmt.Println(key, myMap[key])
	}

	var myMap2 sync.Map
	waitGroup := sync.WaitGroup{}
	waitGroup.Add(1)
	go func() {
		defer waitGroup.Done()
		myMap2.Store("apple", 5)
		fmt.Println("myMap2 loaded")
		// the first one is the value, the second one is a boolean
		// that indicates if the key exists in the map
		if value, ok := myMap2.Load("apple"); ok {
			fmt.Println(value)
		}
	}()
	waitGroup.Wait()
}	