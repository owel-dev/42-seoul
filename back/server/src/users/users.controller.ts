import { Controller, Get, Post, Body, Patch, Param, Delete, UseInterceptors, UploadedFile } from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { FileInterceptor } from '@nestjs/platform-express';
import { multerOptions } from 'src/common/multer';

@Controller('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

	@Post()
	@UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
	create(
		@Body() createUserDto: CreateUserDto,
		@UploadedFile() file: Express.Multer.File
		) {
			return this.usersService.create(createUserDto, file);
		}

	@Get('/:intraid/mypage')
	findOneMyPage(@Param('intraid') intraId : string) {
		return (this.usersService.findOneMyPage(intraId));
	}

	@Patch(':intraid')
	@UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
	update(
		@Param('intraid') intraId: string,
		@Body() updateUserDto: UpdateUserDto,
		@UploadedFile() file: Express.Multer.File
		) {
		return this.usersService.update(intraId, updateUserDto, file);
	}
}
