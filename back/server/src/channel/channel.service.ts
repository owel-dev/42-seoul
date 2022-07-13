import { Injectable } from '@nestjs/common';
import { InjectRepository } from '@nestjs/typeorm';
import { User } from 'src/users/entities/user.entity';
import { Repository } from 'typeorm';
import { GetChannelDto } from './dto/get-channelList.dto';
import { PostChannelDto } from './dto/post-channel.dto';
import { UpdateChannelDto } from './dto/update-channel.dto';
import { ChannelEntity } from './entities/channel.entity';

@Injectable()
export class ChannelService {
  constructor (
    @InjectRepository(ChannelEntity)
    private channelRepository: Repository<ChannelEntity>,

  ){}

  async createChannel(postChannelDto: PostChannelDto) {
    const channel = new ChannelEntity();
    channel.player1 = postChannelDto.player1;
    channel.player2 = postChannelDto.player2;
    channel.intraId = postChannelDto.intraId;
    channel.curNumUser = 0;
    channel.maxNumUser = 10;
    channel.password = postChannelDto.password;
    channel.mode = postChannelDto.mode;
    channel.type = postChannelDto.type;

    await this.channelRepository.save(channel);
  }

  async getAllChannelList() {

    return await this.channelRepository.find();
  }

  async findOne(id: number) {
    console.log(`findone ${id}` );
    console.log(await this.channelRepository.findOneBy(
      {channelId : id}
      ));
    return await this.channelRepository.findOneBy({channelId : id});
  }

  update(id: number, updateChannelDto: UpdateChannelDto) {
    return `This action updates a #${id} channel`;
  }

  remove(id: number) {
    return `This action removes a #${id} channel`;
  }
}
