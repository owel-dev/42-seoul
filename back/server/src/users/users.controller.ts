import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  UseInterceptors,
  UploadedFile,
  Header,
  Headers,
  Query,
  UseGuards,
} from '@nestjs/common';
import { UsersService } from './users.service';
import { CreateUserDto } from './dto/create-user.dto';
import { UpdateUserDto } from './dto/update-user.dto';
import { FileInterceptor } from '@nestjs/platform-express';
import { multerOptions } from 'src/common/multer';
import { AuthGuard } from '@nestjs/passport';
import { Token } from 'src/auth/auth.decorator';
import { ApiTags, ApiOperation } from '@nestjs/swagger';

@Controller('users')
@ApiTags('users')
export class UsersController {
  constructor(private readonly usersService: UsersService) {}

  //   @Post()
  //   @ApiOperation({ summary: ' ', description: ' ' })
  //   @UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
  //   create(
  //     @Body() createUserDto: CreateUserDto,
  //     @UploadedFile() file: Express.Multer.File,
  //   ) {
  //     // console.log(createUserDto);
  //     return this.usersService.create(createUserDto, file);
  //   }

  @Get('/:nickname/mypage')
  @ApiOperation({
    summary: '프로필페이지 유저정보 api',
    description: '프로필페이지에서의 유저정보를 가져옵니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  async findOneMyPage(
    @Token() token: string,
    @Param('nickname') nickName: string,
  ) {
    return await this.usersService.findOneMyPage(token, nickName);
  }

  @Get('/:nickname/modal')
  @ApiOperation({
    summary: '유저모달창 유저정보 api',
    description: '유저모달창에서 필요한 유저정보를 가져옵니다',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  async findOneModal(
    @Param('nickname') nickName: string,
    @Token() token: string,
  ) {
    // console.log("findOneModal");
    // console.log(nickName, token);
    return await this.usersService.findOneModal(token, nickName);
  }

  @Get('/navi')
  @ApiOperation({
    summary: '네비게이션 유저정보 api',
    description: '네비게이션에서 필요한 유저정보를 가져옵니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  async findOneNavi(@Token() token) {
    // console.log("token: ", token);
    return await this.usersService.findOneNavi(token);
  }

  @Patch('/:nickname')
  @ApiOperation({
    summary: '유저 정보 변경 api',
    description: '유저 정보(닉네임, 아바타)를 변경합니다',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  @UseInterceptors(FileInterceptor('avatar', multerOptions('avatar')))
  async update(
    @Param('nickname') nickName: string,
    @Body() updateUserDto: UpdateUserDto,
    @UploadedFile() file: Express.Multer.File,
  ) {
    return await this.usersService.update(nickName, updateUserDto, file);
  }

  //   @Delete(':nickname')
  //   @ApiOperation({ summary: ' ', description: ' ' })
  //   @UseGuards(AuthGuard('jwt-access-token'))
  //   delete(@Param() nickName: string) {
  //     return this.usersService.delete(nickName);
  //   }
}
