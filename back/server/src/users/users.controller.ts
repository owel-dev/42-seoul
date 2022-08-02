import { Controller, Get, Post, Body, Patch, Param, Delete, UseInterceptors, UploadedFile, Header, Headers, Query, UseGuards } from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { FileInterceptor } from '@nestjs/platform-express';
import { multerOptions } from 'src/common/multer';
import { AuthGuard } from '@nestjs/passport';
import { Token } from 'src/auth/auth.decorator';

@Controller('users')
export class UsersController {
	constructor(
		private readonly usersService: UsersService,
	) { }

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
	@UseGuards(AuthGuard('jwt-acess-token'))
	findOneMyPage(@Param('nickname') nickName: string) {
		return (this.usersService.findOneMyPage(nickName));
	}

	@Get('/:nickname/modal')
	@UseGuards(AuthGuard('jwt-acess-token'))
	findOneModal(@Param('nickname') nickName: string, @Token() token: string) {
		console.log("findOneModal");
		console.log(nickName, token);
		return (this.usersService.findOneModal(token, nickName))
	}

	@UseGuards(AuthGuard('jwt-acess-token'))
	@Get('/navi')
	findOneNavi(@Token() token) {
		console.log("token: ", token);
		return (this.usersService.findOneNavi(token));
	}

	@UseGuards(AuthGuard('jwt-acess-token'))
	@Patch('/:nickname')
	@UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
	update(
		@Param('nickname') nickName: string,
		@Body() updateUserDto: UpdateUserDto,
		@Headers() header: string,
		@UploadedFile() file: Express.Multer.File
	) {
		console.log(header);
		console.log(updateUserDto);
		console.log(updateUserDto.avatar);
		console.log(file);
		return this.usersService.update(nickName, updateUserDto, file);
	}

	@UseGuards(AuthGuard('jwt-acess-token'))
	@Delete(':nickname')
	delete(@Param() nickName: string) {
		return this.usersService.delete(nickName);
	}
}
