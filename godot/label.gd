extends Label

var Score := 0

# Method Ingame to increase Score
func increase_score(points: int = 1) -> void:
	Score += points
	text = "Guys: " + str(Score)
