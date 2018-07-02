package main

import (
	"fmt"
	"sort"
	"strings"
	"sync"
)

// ExecutePipeline обеспечивает нам конвейерную обработку функций-воркеров
func ExecutePipeline(fn ...job) {
	prevOut := make(chan interface{}, 1)

	for i, execJob := range fn {
		newChInput := runJob(execJob, prevOut, i)
		prevOut = newChInput
	}

	<-prevOut
	// fmt.Println("ExecutePipeline End")
	return
}

func runJob(fn job, prevOut chan interface{}, i int) chan interface{} {
	result := make(chan interface{}, 1)
	go func(newOut chan interface{}) {
		fn(prevOut, newOut)
		// fmt.Println("Close channel", i)
		close(newOut)
	}(result)
	return result
}

// SingleHash возвращает значение crc32(data)+"~"+crc32(md5(data))
func SingleHash(in, out chan interface{}) {
	mu := &sync.Mutex{}
	wgS := &sync.WaitGroup{}

	for i := range in {
		wgS.Add(1)
		go func(value interface{}, outCh chan interface{}, mu *sync.Mutex, wgS *sync.WaitGroup) {
			// start := time.Now()
			// fmt.Println("SingleHash of (", fmt.Sprint(value), ") run")
			mu.Lock()
			input := []string{fmt.Sprint(value), DataSignerMd5(fmt.Sprint(value))}
			mu.Unlock()
			result := make([]string, 2)

			wg := &sync.WaitGroup{}
			for index := 0; index < 2; index++ {
				wg.Add(1)
				go func(in []string, num int, wg *sync.WaitGroup) {
					in[num] = DataSignerCrc32(input[num])
					wg.Done()
				}(result, index, wg)
			}
			wg.Wait()
			outCh <- strings.Join(result, "~")
			wgS.Done()
			// end := time.Since(start)
			// fmt.Println("SingleHash of (", fmt.Sprint(value), ") time: ", end, " result: ", result)
		}(i, out, mu, wgS)
	}
	wgS.Wait()
}

// MultiHash возвращает значение crc32(th+data))
// где th=0..5 ( т.е. 6 хешей на каждое входящее значение ),
// потом берёт конкатенацию результатов в порядке расчета (0..5)
func MultiHash(in, out chan interface{}) {
	wgM := &sync.WaitGroup{}

	for i := range in {
		wgM.Add(1)
		go func(value interface{}, outCh chan interface{}, wgM *sync.WaitGroup) {
			// start := time.Now()
			// fmt.Println("MultiHash of (", fmt.Sprint(value), ") run")

			result := make([]string, 6)
			wg := &sync.WaitGroup{}
			for index := 0; index < 6; index++ {
				wg.Add(1)
				go func(in []string, num int, wg *sync.WaitGroup) {
					in[num] = DataSignerCrc32(fmt.Sprint(num) + fmt.Sprint(value))
					wg.Done()
				}(result, index, wg)
			}
			wg.Wait()
			outCh <- strings.Join(result, "")
			wgM.Done()
			// end := time.Since(start)
			// fmt.Println("MultiHash of (", fmt.Sprint(value), ") time: ", end, " result: ", result)
		}(i, out, wgM)
	}
	wgM.Wait()
}

// CombineResults получает все результаты, сортирует, объединяет через _ в одну строку
func CombineResults(in, out chan interface{}) {
	result := []string{}
	for i := range in {
		result = append(result, fmt.Sprint(i))
	}
	sort.Strings(result)
	<-in
	out <- strings.Join(result, "_")
}
