package main

import (
	"fmt"
	"os"
	"regexp"
	"time"
)

var (
	re = regexp.MustCompile(`(?m)(\d{1,2}).(\d{1,2}).?`)
)

func main() {
	var start, end, lunch string
	var d1Start, d2Lunch, d3End time.Duration
	var err error
	var workTime, _ = Parse("08:00")

	args := os.Args[1:]

	if len(args) == 0 {
		fmt.Printf("Time start: ")
		fmt.Scanln(&start)

		fmt.Printf("Time lunch: ")
		fmt.Scanln(&lunch)
	} else {
		start = args[0]
		if len(args) > 1 {
			lunch = args[1]
		} else {
			lunch = "00:00"
		}
	}

	if d1Start, err = Parse(start); err != nil {
		panic(err)
	}
	if d2Lunch, err = Parse(lunch); err != nil {
		panic(err)
	}

	end = TimeToHHMM(time.Now().Local())

	if d3End, err = Parse(end); err != nil {
		panic(err)
	}


	diffReal := Sub(d3End, Add(d1Start, d2Lunch))
	diffRemain := Sub(workTime, diffReal)

	fmt.Println("Current time:", end)
	if d3End.Seconds() < Add(d1Start, d2Lunch).Seconds() {
		fmt.Print("You even do not start working!!!")
	} else {
		fmt.Printf("You work: %v, ", re.FindAllStringSubmatch(diffReal.String(), 1)[0][0])
	}

	if diffReal.Minutes() > 480 {
		fmt.Println(", yay, go home! ")
	} else {
		fmt.Printf(" work more! at least %v\n", re.FindAllStringSubmatch(diffRemain.String(), 1)[0][0])
		endTime := time.Now().Local().Add(diffRemain)
		fmt.Println("You can go home after", TimeToHHMM(endTime))
	}

}

// Parse a duration string of "hh:mm" format
func Parse(str string) (time.Duration, error) {
	result := re.FindAllStringSubmatch(str, 1)
	return time.ParseDuration(result[0][1] + "h" + result[0][2] + "m")
}

// Parse a time string to "hh:mm" format
func TimeToHHMM(t time.Time) string {
	var hh, mm string
	if h := t.Hour(); h < 10 {
		hh = fmt.Sprintf("0%v", h)
	} else {
		hh = fmt.Sprintf("%v", h)
	}
	if m := t.Minute(); m < 10 {
		mm = fmt.Sprintf("0%v", m)
	} else {
		mm = fmt.Sprintf("%v", m)
	}

	return fmt.Sprintf("%v:%v", hh, mm)
}

// Sub subtract durations
func Sub(d1, d2 time.Duration) time.Duration {
	epoch := time.Unix(0, 0)
	t1, t2 := epoch.Add(d1), epoch.Add(d2)
	return t1.Sub(t2)
}

func Add(d1, d2 time.Duration) time.Duration {
	r := time.Duration((d1.Seconds() + d2.Seconds()) * float64(time.Second))
	return r
}
