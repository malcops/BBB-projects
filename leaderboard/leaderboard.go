package main

import (
	"fmt"
	"os"

	"github.com/charmbracelet/bubbles/table"
	tea "github.com/charmbracelet/bubbletea"
	"github.com/charmbracelet/lipgloss"
)

var baseStyle = lipgloss.NewStyle().
	BorderStyle(lipgloss.NormalBorder()).
	BorderForeground(lipgloss.Color("240"))

type model struct {
	table table.Model
}

func (m model) Init() tea.Cmd { return nil }

func (m model) Update(msg tea.Msg) (tea.Model, tea.Cmd) {
	var cmd tea.Cmd
	switch msg := msg.(type) {
	case tea.KeyMsg:
		switch msg.String() {
		case "esc":
			if m.table.Focused() {
				m.table.Blur()
			} else {
				m.table.Focus()
			}
		case "q", "ctrl+c":
			return m, tea.Quit
		case "enter":
			return m, tea.Batch(
				tea.Printf("Let's go %s!", m.table.SelectedRow()[1]),
			)
		}
	}
	m.table, cmd = m.table.Update(msg)
	return m, cmd
}

func (m model) View() string {
	return baseStyle.Render(m.table.View()) + "\n"
}

func main() {
	columns := []table.Column{
		{Title: "Rank", Width: 4},
		{Title: "Name", Width: 20},
		{Title: "Score", Width: 5},
		{Title: "Thru", Width: 5},
	}

	rows := []table.Row{
		{"1", "Bryson Dechambeau", "-5", "15"},
		{"2", "Rory McIlroy", "-4", "15"},
		{"3", "Rickie Fowler", "-4", "14"},
		{"4", "Hideki Matsuyama", "-3", "F"},
		{"5", "Corey Connors", "-3", "F"},
		{"6", "Tiger Woods", "-2", "F"},
		{"7", "Phil Mickelson", "-1","16"},
		{"8", "John Rahm", "-1", "F"},
		{"9", "Tommy Fleetwood", "-1", "F"},
		{"10", "Shane Lowry", "-1", "16"},
		{"11", "Scottie Scheffler", "E", "17"},
		{"12", "Colin Morikawa", "E", "17"},
		{"13", "Cameron Young", "E", "F"},
		{"14", "Gary Woodland", "E", "F"},
		{"15", "Brooks Koepka", "+1", "F"},
	}

	t := table.New(
		table.WithColumns(columns),
		table.WithRows(rows),
		table.WithFocused(true),
		table.WithHeight(7),
	)

	s := table.DefaultStyles()
	s.Header = s.Header.
		BorderStyle(lipgloss.NormalBorder()).
		BorderForeground(lipgloss.Color("240")).
		BorderBottom(true).
		Bold(false)
	s.Selected = s.Selected.
		Foreground(lipgloss.Color("229")).
		Background(lipgloss.Color("57")).
		Bold(false)
	t.SetStyles(s)

	m := model{t}
	if _, err := tea.NewProgram(m).Run(); err != nil {
		fmt.Println("Error running program:", err)
		os.Exit(1)
	}
}

