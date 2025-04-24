package main

import (
    "bufio"
    "fmt"
    "os"
    "strings"
    "unicode"
)

type Command int

const (
    CREATE_PLANE Command = iota
    PLANES_FOR_TOWN
    TOWNS_FOR_PLANE
    PLANES
    EXIT
    UNKNOWN
)

func parseCommand(input string) Command {
    cmd := strings.ToUpper(input)

    switch cmd {
    case "CREATE_PLANE":
        return CREATE_PLANE
    case "PLANES_FOR_TOWN":
        return PLANES_FOR_TOWN
    case "TOWNS_FOR_PLANE":
        return TOWNS_FOR_PLANE
    case "PLANES":
        return PLANES
    case "EXIT":
        return EXIT
    default:
        return UNKNOWN
    }
}

func split(s string) []string {
    return strings.FieldsFunc(s, func(c rune) bool {
        return unicode.IsSpace(c)
    })
}

func main() {
    system := NewPlaneSystem()
    reader := bufio.NewReader(os.Stdin)

    fmt.Println("CREATE_PLANE <plane> <town1> <town2> ...")
    fmt.Println("PLANES_FOR_TOWN <town>")
    fmt.Println("TOWNS_FOR_PLANE <plane>")
    fmt.Println("PLANES")
    fmt.Println("EXIT")

    for {
        line, _ := reader.ReadString('\n')
        line = strings.TrimSpace(line)
        if line == "" {
            continue
        }

        tokens := split(line)
        if len(tokens) == 0 {
            continue
        }

        cmd := parseCommand(tokens[0])

        switch cmd {
        case CREATE_PLANE:
            if len(tokens) >= 3 {
                plane := tokens[1]
                towns := tokens[2:]
                system.CreatePlane(plane, towns)
            } else {
                fmt.Println("Неверные параметры: CREATE_PLANE <plane> <town1> <town2> ...")
            }
        case PLANES_FOR_TOWN:
            if len(tokens) == 2 {
                system.PlanesForTown(tokens[1])
            } else {
                fmt.Println("Неверные параметры: PLANES_FOR_TOWN <town>")
            }
        case TOWNS_FOR_PLANE:
            if len(tokens) == 2 {
                system.TownsForPlane(tokens[1])
            } else {
                fmt.Println("Неверные параметры: TOWNS_FOR_PLANE <plane>")
            }
        case PLANES:
            system.All()
        case EXIT:
            return
        case UNKNOWN:
            fallthrough
        default:
            fmt.Println("Неверная команда")
        }
    }
}
