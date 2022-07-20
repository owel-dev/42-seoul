import { Controller, Get, Post, Body, Patch, Param, Delete, UseInterceptors, UploadedFile, Header, Headers, Query } from '@nestjs/common';
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
			console.log(createUserDto);
			return this.usersService.create(createUserDto, file);
		}

	@Get('/:nickname/mypage')
	findOneMyPage(@Param('nickname') nickName : string) {
		return (this.usersService.findOneMyPage(nickName));
	}

	@Get('/:nickname/modal')
	findOneModal(@Param('nickname') nickName : string, @Query('user') requester : string) {
		console.log(requester, nickName);
		return (this.usersService.findOneModal(requester, nickName))
	}

	@Patch('/:nickname')
	@UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
	update(
		@Param('nickname') nickName: string,
		@Body() updateUserDto: UpdateUserDto,
		@Headers() header: string,
		@UploadedFile() file: Express.Multer.File,
		) {
			console.log(header);
			console.log(updateUserDto);
			console.log(updateUserDto.avatar);
			console.log(file);
			return this.usersService.update(nickName, updateUserDto, file);
		}
	
	@Delete(':nickname')
	delete(@Param() nickName: string) {
		return this.usersService.delete(nickName);
	}
}