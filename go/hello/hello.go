package main

import "fmt"

import "rsc.io/quote" // go mod tidy

func main() {
    fmt.Println(quote.Go())
}