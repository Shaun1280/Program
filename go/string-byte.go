package main

import (
	"bytes"
	"fmt"
)

func main() {
	s := "hello, 世界"
	println(s)

	// convert to bytes
	bts := []byte(s)
	// mute one char
	bts[0] = 'c'
	println(bts)
	// print len of bytes
	println(len(bts))
	// convert back to string
	backToString := string(bts)
	
	println(backToString)

	var buffer bytes.Buffer
	buffer.WriteString("hello")
	buffer.WriteByte(' ')
	buffer.WriteString("world")
	fmt.Println(buffer.String())
}