import {Controller, 
  Get, 
  Post,
  Body, 
  Param, 
  Delete, 
  UploadedFiles, 
  UseInterceptors
} from '@nestjs/common';
import { FilesInterceptor } from '@nestjs/platform-express'
import { CreateImageDto } from './dto/create-image.dto';
import {ImagesService} from './images.service';
import { Image } from './interfaces/image.interface';
import { diskStorage } from 'multer';
import { extname, join } from 'path';
import { existsSync, mkdirSync } from 'fs';
import { Request } from 'express';

interface UploadRequest extends Request {

  uploadFolder?: string;

}
@Controller('images')
export class ImagesController {
  constructor(private imagesService: ImagesService) {}

  @Post()
  async create(@Body() createImageDto : CreateImageDto){
    this.imagesService.create(createImageDto);
  }

  

  @Post('upload')
  @UseInterceptors(FilesInterceptor('images', 50, {
    storage: diskStorage({
      destination: (req: UploadRequest, file, cb)=>{
        if(!req.uploadFolder){
          req.uploadFolder = Date.now() + '-' + Math.round(Math.random() * 1e9);
        }
        const uploadPath = join('./uploads', req.uploadFolder);
        if (!existsSync(uploadPath)) {
          mkdirSync(uploadPath, { recursive: true });
        }
        
        cb(null, uploadPath);
      },
      filename: (req, file, cb) => {
        const uniqueName = Date.now() + '-' + Math.round(Math.random()* 1e9);
        cb(null, uniqueName + extname(file.originalname));
      },
    }),
  })
)
  uploadImages(@UploadedFiles() files: Express.Multer.File[]){
    console.log(files);
    return{
      message: 'Images uploaded succesfully',
      count: files.length,
      files: files.map((file) => ({
        originalName: file.originalname,
        mimeType: file.mimetype,
        size: file.size,
      })),
    };
  }

  @Delete(':id')
  remove(@Param('id') id: string) {
    return `This action removes a #${id} image`;
  }

  @Get()
  async findAll(): Promise<Image[]> {
    return this.imagesService.findAll();
  }
}
