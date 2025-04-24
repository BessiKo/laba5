package main

import (
    "fmt"
    "strings"
)

type PlaneSystem struct {
    planeRoutes map[string][]string
    townPlanes  map[string]map[string]struct{}
}

func NewPlaneSystem() *PlaneSystem {
    return &PlaneSystem{
        planeRoutes: make(map[string][]string),
        townPlanes:  make(map[string]map[string]struct{}),
    }
}

func (ps *PlaneSystem) CreatePlane(plane string, towns []string) {
    if _, exists := ps.planeRoutes[plane]; exists {
        fmt.Printf("Plane %s already exists!\n", plane)
        return
    }

    ps.planeRoutes[plane] = towns

    for _, town := range towns {
        if _, exists := ps.townPlanes[town]; !exists {
            ps.townPlanes[town] = make(map[string]struct{})
        }
        ps.townPlanes[town][plane] = struct{}{}
    }

    fmt.Printf("Plane %s created with %d stops.\n", plane, len(towns))
}

func (ps *PlaneSystem) PlanesForTown(town string) {
    planes, exists := ps.townPlanes[town]
    if !exists {
        fmt.Printf("No planes found for town %s\n", town)
        return
    }

    fmt.Printf("Planes passing through %s:\n", town)
    for plane := range planes {
        fmt.Printf("- %s\n", plane)
    }
}

func (ps *PlaneSystem) TownsForPlane(plane string) {
    towns, exists := ps.planeRoutes[plane]
    if !exists {
        fmt.Printf("Plane %s not found!\n", plane)
        return
    }

    fmt.Printf("Route for plane %s:\n", plane)
    for _, town := range towns {
        fmt.Printf("- %s", town)

        otherPlanes, exists := ps.townPlanes[town]
        if exists && len(otherPlanes) > 1 {
            fmt.Print(" (other planes: ")
            first := true
            for otherPlane := range otherPlanes {
                if otherPlane != plane {
                    if !first {
                        fmt.Print(", ")
                    }
                    fmt.Print(otherPlane)
                    first = false
                }
            }
            fmt.Print(")")
        }
        fmt.Println()
    }
}

func (ps *PlaneSystem) All() {
    if len(ps.planeRoutes) == 0 {
        fmt.Println("No planes registered!")
        return
    }

    fmt.Println("All registered planes:")
    for plane, towns := range ps.planeRoutes {
        fmt.Printf("- %s (stops: %s)\n", plane, strings.Join(towns, ", "))
    }
}
