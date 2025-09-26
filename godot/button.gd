extends Button

signal scoredClick(points)
signal spawnGuy()

func _ready():
	self.pressed.connect(_on_pressed)

func _on_pressed():
	print("BingBong")
	emit_signal("scoredClick", 1)
	emit_signal("spawnGuy")  
