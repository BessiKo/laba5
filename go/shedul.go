package main

import (
	"bufio"
	"fmt"
	"os"
	"strconv"
	"strings"
)

// Структура для хранения расписания
type Schedule struct {
	thisMonth map[int]map[string]int // {{день, {"дисциплина", кол-во}}, {}, {}}
	nextMonth map[int]map[string]int
	days      int
}

// Конструктор для инициализации расписания
func NewSchedule() *Schedule {
	return &Schedule{
		thisMonth: make(map[int]map[string]int),
		nextMonth: make(map[int]map[string]int),
		days:      31,
	}
}

// Метод для добавления пары в расписание
func (s *Schedule) Class(day int, subject string) {
	if day < 1 || day > s.days {
		fmt.Printf("Такого дня нет: %d\n", day)
		return
	}
	if _, exists := s.thisMonth[day]; !exists {
		s.thisMonth[day] = make(map[string]int)
	}
	s.thisMonth[day][subject]++ // Увеличение количества пар для данной дисциплины в указанный день
}

// Метод для перехода на следующий месяц
func (s *Schedule) Next() {
	s.nextMonth = make(map[int]map[string]int) // Очистка данных следующего месяца
	daysNext := 30
	if s.days == 30 {
		daysNext = 31
	}

	// Переносим все занятия на предпоследний день следующего месяца
	penultimate := daysNext - 1 // предпоследний день

	for day, subjects := range s.thisMonth {
		if day <= daysNext {
			for subject, count := range subjects {
				if _, exists := s.nextMonth[day]; !exists {
					s.nextMonth[day] = make(map[string]int)
				}
				s.nextMonth[day][subject] += count // Перенос пар в следующий месяц
			}
		} else {
			for subject, count := range subjects {
				if _, exists := s.nextMonth[penultimate]; !exists {
					s.nextMonth[penultimate] = make(map[string]int)
				}
				s.nextMonth[penultimate][subject] += count // Перенос пар на предпоследний день
			}
		}
	}

	s.thisMonth = s.nextMonth // Перенос данных следующего месяца в текущий месяц
	s.days = daysNext
}

// Метод для вывода расписания на указанный день
func (s *Schedule) View(day int) {
	if day < 1 || day > s.days {
		fmt.Printf("Такого дня нет: %d\n", day)
		return
	}

	subjects, exists := s.thisMonth[day]
	if !exists || len(subjects) == 0 { // Проверка, есть ли пары в этот день
		fmt.Printf("In %d day we are free!\n", day)
	} else {
		fmt.Printf("In %d day classes in university: ", day)
		for subject, count := range subjects {
			fmt.Printf("%s(%d) ", subject, count)
		}
		fmt.Println()
	}
}

// Функция для разбиения строки на токены
func split(s string) []string {
	return strings.Fields(s)
}

func main() {
	schedule := NewSchedule()
	reader := bufio.NewReader(os.Stdin)

	fmt.Print("Введите количество команд: ")
	input, _ := reader.ReadString('\n')
	N, _ := strconv.Atoi(strings.TrimSpace(input))

	for i := 0; i < N; i++ {
		input, _ := reader.ReadString('\n')
		tokens := split(strings.TrimSpace(input))

		if len(tokens) == 0 {
			continue
		}

		command := tokens[0]
		if command == "CLASS" && len(tokens) >= 3 {
			day, _ := strconv.Atoi(tokens[1])
			subject := strings.Join(tokens[2:], " ")
			schedule.Class(day, subject)
		} else if command == "NEXT" {
			schedule.Next()
		} else if command == "VIEW" && len(tokens) >= 2 {
			day, _ := strconv.Atoi(tokens[1])
			schedule.View(day)
		} else {
			fmt.Println("Ошибка")
		}
	}
}
