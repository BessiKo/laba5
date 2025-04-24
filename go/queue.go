package main

import (
	"fmt"
	"sort"
	"strconv"
)

// Структура для хранения информации о посетителе - время и номер
type Visitor struct {
	time  int
	coupon string
}

// Глобальная переменная для выдачи уникальных талончиков
var counter = 0

// Функция для выдачи уникального талончика
func Coupon() string {
	counter++
	return "T" + strconv.Itoa(counter-1)
}

// Функция для добавления посетителя в очередь
func inEnqueue(queue *[]Visitor, time int) {
	visitor := Visitor{time: time, coupon: Coupon()}
	*queue = append(*queue, visitor)
	fmt.Println(visitor.coupon)
}

// Функция для распределения посетителей по окнам
func okno(queue *[]Visitor, countWindows int) {
	windows := make([][]Visitor, countWindows) // Посетителей в каждом окне
	windowEndTimes := make([]int, countWindows) // Время окончания обслуживания в каждом окне

	// Сортируем посетителей по убыванию времени обслуживания
	sort.Slice(*queue, func(i, j int) bool {
		return (*queue)[i].time > (*queue)[j].time
	})

	// Распределяем посетителей по окнам
	for _, visitor := range *queue {
		// Найти окно с минимальным временем окончания обслуживания - индекс
		minIndex := 0
		for i := 1; i < countWindows; i++ {
			if windowEndTimes[i] < windowEndTimes[minIndex] {
				minIndex = i
			}
		}
		windows[minIndex] = append(windows[minIndex], visitor)
		windowEndTimes[minIndex] += visitor.time
	}

	// Вывод информации о распределении посетителей по окнам
	for i := 0; i < countWindows; i++ {
		fmt.Printf("Окно %d (%d минут):", i+1, windowEndTimes[i])
		for _, visitor := range windows[i] {
			fmt.Printf(" %s", visitor.coupon)
		}
		fmt.Println()
	}
}

func main() {
	var countWindows int
	fmt.Print("Кол-во окон: ")
	fmt.Scan(&countWindows)

	var queue []Visitor
	var command string
	var time int

	for {
		fmt.Scan(&command)
		if command == "ENQUEUE" {
			fmt.Scan(&time)
			inEnqueue(&queue, time)
		} else if command == "DISTRIBUTE" {
			okno(&queue, countWindows)
			break
		}
	}
}
