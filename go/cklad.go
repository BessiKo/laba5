package main

import (
	"fmt"
	"strings"
)

// Структура для хранения информации о товаре в ячейке
type Cell struct {
	product  string
	quantity int
}

// Глобальная переменная для хранения состояния склада
var store = make(map[string][]Cell)

// Функция для получения количества товаров в ячейке
func Quantity(address string) int {
	count := 0
	cellVector := store[address]
	for _, cell := range cellVector {
		count += cell.quantity
	}
	return count
}

// Функция для инициализации склада
func Creation() {
	areas := []string{"A", "B"}
	for _, area := range areas {
		for rack := 1; rack <= 6; rack++ {
			for section := 1; section <= 4; section++ {
				for shelf := 1; shelf <= 4; shelf++ {
					address := fmt.Sprintf("%s%d%d%d", area, rack, section, shelf)
					store[address] = []Cell{}
				}
			}
		}
	}
}

// Функция для добавления товара в ячейку
func add(product string, quantity int, address string) {
	if _, exists := store[address]; !exists {
		fmt.Println("Такого адреса не существует")
		return
	}

	can := 10 - Quantity(address)
	if quantity > can {
		fmt.Printf("По данному адресу вы можете положить не более %d единиц товара.\n", can)
		return
	}

	cellVector := store[address]
	for i := range cellVector {
		if cellVector[i].product == product {
			cellVector[i].quantity += quantity
			return
		}
	}

	store[address] = append(cellVector, Cell{product, quantity})
}

// Функция для удаления товара из ячейки
func remove(product string, quantity int, address string) {
	if _, exists := store[address]; !exists {
		fmt.Println("Такого адреса не существует")
		return
	}

	cellVector := store[address]
	for i := range cellVector {
		if cellVector[i].product == product {
			if cellVector[i].quantity < quantity {
				fmt.Println("Вы удаляете больше единиц товара, чем есть в ячейке")
				return
			}
			cellVector[i].quantity -= quantity
			if cellVector[i].quantity == 0 {
				store[address] = append(cellVector[:i], cellVector[i+1:]...)
			}
			return
		}
	}

	fmt.Println("Такого товара нет, чтобы его удалять")
}

// Функция для вывода информации о состоянии склада
func info() {
	totalCapacity := 1920
	totalItems := 0
	zoneACapacity := 960
	zoneBCapacity := 960
	zoneAItems := 0
	zoneBItems := 0

	fmt.Println("Состояние склада:")
	for address, cellVector := range store {
		if len(cellVector) > 0 {
			fmt.Printf("%s: ", address)
			for _, cell := range cellVector {
				if cell.quantity > 0 {
					fmt.Printf("%s (%d шт.) ", cell.product, cell.quantity)
					totalItems += cell.quantity
					if strings.HasPrefix(address, "A") {
						zoneAItems += cell.quantity
					} else if strings.HasPrefix(address, "B") {
						zoneBItems += cell.quantity
					}
				}
			}
			fmt.Println()
		}
	}

	fmt.Println("Пустые ячейки:")
	for address := range store {
		if len(store[address]) == 0 || Quantity(address) == 0 {
			fmt.Printf("%s ", address)
		}
	}
	fmt.Println()

	fmt.Printf("Склад загружен на: %.2f%%\n", float64(totalItems)/float64(totalCapacity)*100)
	fmt.Printf("Зона A загружена на: %.2f%%\n", float64(zoneAItems)/float64(zoneACapacity)*100)
	fmt.Printf("Зона B загружена на: %.2f%%\n", float64(zoneBItems)/float64(zoneBCapacity)*100)
}

func main() {
	Creation()
	var command, product, address string
	var quantity int

	for {
		fmt.Scan(&command)
		switch command {
		case "ADD":
			fmt.Scan(&product, &quantity, &address)
			add(product, quantity, address)
		case "REMOVE":
			fmt.Scan(&product, &quantity, &address)
			remove(product, quantity, address)
		case "INFO":
			info()
		case "EXIT":
			return
		default:
			fmt.Println("Такой команды не существует")
		}
	}
}
