import { Button } from "@/components/ui/button"
import {
  Card,
  CardContent,
  CardHeader,
  CardTitle,
} from "@/components/ui/card"
import { Input } from "@/components/ui/input"
import { Label } from "@/components/ui/label"

import { useState, useEffect, useRef} from "react"

function Home() {

  const [images, setImages] = useState<File[]>([]);
  const inputRef = useRef<HTMLInputElement | null>(null);

  useEffect(() => {
    console.log(images)
  }, [images]);

  function handleInput(e){
    const files = Array.from(e.target.files ?? []);
    console.log(files);
    const imageFiles = files.filter((file) => 
      file.type.startsWith("image/")
    );
    console.log(imageFiles)
    setImages(imageFiles)
  }
  
  function handleReset(){
    setImages([]);
    if(inputRef.current){
      inputRef.current.value = "";
    }
  }

  const processImages = (async()=>{
    if(inputRef.current){
      const formData = new FormData();
      images.forEach((image) => {
        formData.append("images", image);
      });
      const res = await fetch("http://localhost:3000/images/upload", {
        method: "POST",
        body: formData
      })
      const data = await res.json();
      console.log(data);
      handleReset();
    }
  })

  return (
    <main className="min-h-screen bg-background p-8">
      <section className="mx-auto max-w-4xl space-y-8">
        <div>
          <h1 className="text-4xl font-bold tracking-tight">
            Image Processor
          </h1>
          <p className="mt-2 text-muted-foreground">
            Upload an image and apply filters, resizing, or compression.
          </p>
        </div>

        <Card>
          <CardHeader>
            <CardTitle>Upload image</CardTitle>
          </CardHeader>

          <CardContent className="space-y-4">
            <div className="space-y-2">
              <Label htmlFor="image">Image file</Label>
              <Input
                ref = {inputRef}
                type = "file"
                webkitdirectory=""
                directory=""
                multiple
                onChange = {handleInput}
              />
            </div>

            <div className="flex gap-3">
              <Button onClick = {processImages}>Process Images</Button>
              <Button variant="outline" onClick = {handleReset}>Reset</Button>
            </div>
          </CardContent>
        </Card>
      </section>
    </main>
  )
}
export default Home