if __name__ == "__main__":
	for i in range(13):
		for j in range(7):
			s = "res/testres" + str(2 ** j) + "c3s" + str(i) + "l.txt"
			with open(s, "r") as f:
				data = f.readlines();
			print(data[2][data[2].index(":")+2:-1] + "," + data[23][data[23].index(":")+2:-1])
		print("\n")
