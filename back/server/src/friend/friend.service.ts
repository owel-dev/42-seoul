import { HttpException, HttpStatus, Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { AuthService } from 'src/auth/auth.service';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { CreateFriendDto } from './dto/create-friend.dto';
import { ResFriendDto } from './dto/res-friend.dto';
import { Friend } from './entities/friend.entity';

@Injectable()
export class FriendService {
  constructor(
    @InjectRepository(Friend)
    private friendRepository: Repository<Friend>,
    @InjectRepository(User)
    private userRepository: Repository<User>,
    private readonly authService: AuthService,
  ) {}

  async create(token: string, createFriendDto: CreateFriendDto) {
    // console.log('Friend created');
    const friend1 = await this.userRepository.findOne({
      where: { nickname: createFriendDto.player1 },
    });
    const friend2 = await this.userRepository.findOne({
      where: { nickname: createFriendDto.player2 },
    });
    if (!friend1)
      throw new HttpException(
        {
          statusCode: 'FA02',
          error: `${createFriendDto.player1}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    if (!friend2)
      throw new HttpException(
        {
          statusCode: 'FA02',
          error: `${createFriendDto.player1}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    const alreadyFriend = await this.friendRepository.findOne({
      relations: ['friend_1', 'friend_2'],
      where: {
        friend_1: friend1,
        friend_2: friend2,
      },
    });
    if (alreadyFriend !== null)
      throw new HttpException(
        {
          statusCode: 'FA01',
          error: `Already Friend`,
        },
        HttpStatus.BAD_REQUEST,
      );
    const friend = new Friend();
    friend.friend_1 = friend1;
    friend.friend_2 = friend2;
    return this.friendRepository.save(friend);
  }

  async getFriendListOne(nickName: string) {
    if (
      (await this.userRepository.findOneBy({ nickname: nickName })) ===
      undefined
    )
      throw new HttpException(
        {
          statusCode: 'FA02',
          error: `${nickName}: Cannot find user`,
        },
        HttpStatus.BAD_REQUEST,
      );
    const friendRepo = await this.friendRepository.find({
      relations: {
        friend_1: true,
        friend_2: true,
      },
      where: { friend_1: { nickname: nickName } },
    });
    const resFrinedListDto = friendRepo.map((friend, index, array) => {
      const resFriend = new ResFriendDto();
      resFriend.nickName = friend.friend_2.nickname;
      resFriend.status = friend.friend_2.status;
    });
    return resFrinedListDto;
  }

  async deletefriend(token: string, nickName: string) {
    // console.log('delete friend');
    const reqUser = await this.authService.getUserNickByToken(token);
    const findFriend = await this.friendRepository.findOne({
      relations: ['friend_1', 'friend_2'],
      where: {
        friend_1: { nickname: reqUser },
        friend_2: { nickname: nickName },
      },
    });
    if (!findFriend)
      throw new HttpException(
        { statusCode: 'FD01', error: 'Not friend' },
        HttpStatus.BAD_REQUEST,
      );
    await this.friendRepository.delete(findFriend);
  }
}
