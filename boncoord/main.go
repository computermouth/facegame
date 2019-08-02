package main

import (
	"github.com/go-yaml/yaml"
	"io/ioutil"
	"log"
	"os"
	"path/filepath"
	"strings"
)

type Sprite struct {
	Spritename string
	Animations []struct {
		Animation string `yaml:"animation"`
		Frames    []struct {
			Frame  string `yaml:"frame"`
			Delay  int    `yaml:"delay"`
			Layers []struct {
				Layer     string `yaml:"layer"`
				ImgBase64 string `yaml:"imgBase64,omitempty"`
				Path      string `yaml:"path,omitempty"`
				XImage    int    `yaml:"x_image"`
				YImage    int    `yaml:"y_image"`
				Color     string `yaml:"color"`
				X         []int `yaml:"x,omitempty"`
				Y         []int `yaml:"y,omitempty"`
			} `yaml:"layers"`
		} `yaml:"frames"`
	} `yaml:"animations"`
}

func main() {

	for i := 1; i < len(os.Args); i++ {

		fullpath := os.Args[i]
		directory := filepath.Dir(fullpath)
		filename := filepath.Base(os.Args[i])

		s := Sprite{Spritename: strings.TrimSuffix(filename, filepath.Ext(filename))}

		data, err := ioutil.ReadFile(fullpath)
		if err != nil {
			log.Fatalf("error: %v", err)
		}

		err = yaml.Unmarshal([]byte(data), &s)
		if err != nil {
			log.Fatalf("error: %v", err)
		}
		
		var widths []int
		
		// find widest for each layer
		for _, anim := range s.Animations {
			
			for _, frame := range anim.Frames{
				
				for _, layer := range frame.Layers{
				
					widest := 0
					
					if layer.Color == "" {
						continue
					}
					
					for _, xpos := range layer.X {
						if xpos > widest {
							widest = xpos
						}
					}
					
					log.Printf("append: %d\n", widest)
					widths = append(widths, widest)
				}
				
			}
			
		}
		
		log.Println(len(widths))
		
		// flip x on it's center
		for a, anim := range s.Animations {
			
			for f, frame := range anim.Frames{
				
				for l, layer := range frame.Layers{
					
					if layer.Color == "" {
						continue
					}
					
					for x, xpos := range layer.X {
					
						index := a + f + l + x
						log.Println(x)
						log.Println(xpos)
						log.Println(layer.Layer)
						log.Println(index)
						if layer.X[x] >= widths[index] / 2 {
							layer.X[x] = (widths[index] / 2) + layer.X[x]
						} else {
							layer.X[x] = (widths[index] / 2) - layer.X[x]
						}
						
					}
				}
				
			}
			
		}
		
		cout := directory + "/" + s.Spritename + ".flip.yaml"
		log.Printf(directory)
		log.Printf(cout)
		
		f, err := os.Create(cout)
		if err != nil {
			log.Fatalf("error: %v", err)
		}
		
		d, err := yaml.Marshal(&s.Animations)
		if err != nil {
			log.Fatalf("error: %v", err)
		}
		
		f.Write(d)
		
		f.Close()
	}

}
