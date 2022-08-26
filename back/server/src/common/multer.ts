import * as multer from 'multer';

import * as path from 'path';

import * as fs from 'fs';

import { MulterOptions } from '@nestjs/platform-express/multer/interfaces/multer-options.interface';
import { BadRequestException, HttpException, HttpStatus } from '@nestjs/common';

const createFolder = (folder: string) => {
  try {
    // console.log('💾 Create a root uploads folder...');

    fs.mkdirSync(path.join(__dirname, '../../', `uploads`)); //폴더를 만드는 명령어
  } catch (error) {
    // console.log('The folder already exists...');
  }

  try {
    // console.log(`💾 Create a ${folder} uploads folder...`);

    fs.mkdirSync(path.join(__dirname, '../../', `uploads/${folder}`)); //폴더 생성
  } catch (error) {
    // console.log(`The ${folder} folder already exists...`);
  }
};

const storage = (folder: string): multer.StorageEngine => {
  createFolder(folder); // 폴더 만들고
  return multer.diskStorage({
    //옵션을 써준다.
    destination(req, file, cb) {
      const folderName = path.join(__dirname, '../../', `uploads/${folder}`);
      cb(null, folderName); //callback에 두번째 인자가 어디에 저장할지다.
    },

    filename(req, file, cb) {
      const ext = path.extname(file.originalname); //파일을 올려서 확장자를 추출한다.

      const ts = Date.now();
      const data_ob = new Date(ts);
      const year = data_ob.getFullYear();
      const month = data_ob.getMonth();
      const date = data_ob.getDate();
      const hour = data_ob.getHours();
      const min = data_ob.getMinutes();
      const sec = data_ob.getSeconds();
      const fileName = `${path.basename(
        file.originalname,

        ext,
      )}${year}${month}${date}${hour}${min}${sec}${ext}`;

      cb(null, fileName);
    },
  });
};

// multerOptions을 컨트롤러에서 사용해서 업로드 한다.
export const multerOptions = (folder: string) => {
  const result: MulterOptions = {
    fileFilter: (request, file, callback) => {
      if (!file.mimetype.match(/\/(jpg|jpeg|png|gif)$/)) {
        // 이미지 형식은 jpg, jpeg, png, gif만 허용합니다.
        callback(
          new HttpException(
            { statusCode: 'AC01', error: 'Invalid image extension' },
            HttpStatus.BAD_REQUEST,
          ),
          false,
        );
      } else if (file.size > 10 * 1024 * 1024) {
        callback(
          new HttpException(
            { statusCode: 'AC02', error: 'File size is too big' },
            HttpStatus.BAD_REQUEST,
          ),
          false,
        );
      } else {
        callback(null, true);
      }
    },
    storage: storage(folder),
    limits: { fileSize: 10 * 1024 * 1024 },
  };

  return result;
};
