import {
  Controller,
  Get,
  Post,
  Body,
  Patch,
  Param,
  Delete,
  Query,
  HttpCode,
  UseGuards,
} from '@nestjs/common';
import { FriendService } from './friend.service';
import { CreateFriendDto } from './dto/create-friend.dto';
import { UpdateFriendDto } from './dto/update-friend.dto';
import { DeleteFriendDto } from './dto/delete-friend.dto';
import { AuthGuard } from '@nestjs/passport';
import { Token } from 'src/auth/auth.decorator';
import { ApiTags, ApiOperation, ApiResponse } from '@nestjs/swagger';

@Controller('friend')
@ApiTags('친구 관련 API')
export class FriendController {
  constructor(private readonly friendService: FriendService) {}

  @Post()
  @ApiOperation({ summary: '친구 추가 API', description: '친구 추가 API' })
  @UseGuards(AuthGuard('jwt-access-token'))
  create(@Token() token: string, @Body() createFriendDto: CreateFriendDto) {
    return this.friendService.create(token, createFriendDto);
  }

  @Get(':nickname')
  @ApiOperation({
    summary: '친구 목록 API',
    description: '친구 리스트를 가져옵니다',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  findOne(@Param('nickname') nickName: string) {
    return this.friendService.getFriendListOne(nickName);
  }

  @Delete()
  @ApiOperation({
    summary: '친구 삭제 API',
    description: '유저간의 친구 관계를 삭제합니다.',
  })
  @UseGuards(AuthGuard('jwt-access-token'))
  @HttpCode(204)
  deleteFriend(@Token() token: string, @Query('user') nickName) {
    return this.friendService.deletefriend(token, nickName);
  }
}
