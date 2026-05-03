import { useState } from "react";
import { Input } from "@/components/ui/input"
function FolderUpload() {
  const [images, setImages] = useState([]);

  function handleFolderChange(e) {
    const files = Array.from(e.target.files);

    const imageFiles = files.filter((file) =>
      file.type.startsWith("image/")
    );

    setImages(imageFiles);

    console.log("All files:", files);
    console.log("Images only:", imageFiles);
  }

  return (
    <div>
      <input
        type="file"
        webkitdirectory="true"
        directory=""
        multiple
        onChange={handleFolderChange}
      />
      <Input id="image" type="file" accept="image/*" />
      <p>{images.length} images selected</p>

      <div>
        {images.map((file, index) => (
          <div key={index}>
            <p>{file.webkitRelativePath}</p>
            <img
              src={URL.createObjectURL(file)}
              alt={file.name}
              width="150"
            />
          </div>
        ))}
      </div>
    </div>
  );
}

export default FolderUpload;