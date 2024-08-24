package main

import "fmt"

type Speaker interface {
	Speak()
}

type Person struct {
	Name string
}

type Robot struct {
	ID string
}

func (p *Person) SayHello() { // * avoids copying the struct
	fmt.Println("Hello,", p.Name)
}

func (p *Person) Speak() {
	fmt.Println("I am a person, my name is ", p.Name)
}

func (r *Robot) Speak() {
	fmt.Println("I am a robot, my ID is ", r.ID)
}

func main() {
	p := Person{Name: "John"}
	p.SayHello()
	p.Speak()

	r := Robot{ID: "1234"}
	hellos := []Speaker{&p, &r}
	for _, h := range hellos {
		h.Speak()
	}
}